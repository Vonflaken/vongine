#ifndef __VGOBJECTPOOL_H__
#define __VGOBJECTPOOL_H__

#include "VGMacros.h"
#include "base/VGEntity.h"

#include <unordered_map>
#include <memory>

NS_VG_BEGIN

/**
* Implementation of the pattern: Object Pooling for game entities.
* Intended to use with Entity sub-classes.
* Override "Init(const glm::vec3& position)" func for custom initialization.
*/
template <typename T>
class DLLAPI ObjectPool
{
public:
	/**
	* Initialize pool instancing 'size' number of objects.
	*/
	bool Init(const uint32 size)
	{
		_pool.reserve(size);

		// Instance all initial entities
		for (uint32 i = 0; i < size; i++)
		{
			std::shared_ptr<Entity> object(new T());
			if (object->Init(glm::vec3(9999.f)))
				Recycle(object);
		}
		return true;
	}

	/**
	* Will set a object at given position with given rotation.
	* Will create a new one if all in pool are already in use. This will increase size of pool.
	* @param parent The new parent of next object pulled off.
	*/
	std::shared_ptr<T> Spawn(const glm::vec3& position, const glm::vec3& eulerAngles, Entity* parent)
	{
 		std::shared_ptr<Entity> object = nullptr;
		if (parent)
		{			
			// Find first available object
			for (auto pair : _pool)
			{
				if (pair.second) // Is available?
				{
					object = pair.first;
					break;
				}
			}

			if (!object) // If there are not availables objects
			{
				// Create new one
				std::shared_ptr<Entity> newObject(new T());
				if (newObject->Init(glm::vec3(9999.f)))
				{
					Recycle(newObject); // Add to pool
					object = newObject;
				}
			}

			if (object)
			{
				_pool[object] = false; // Mark as in use
				// Re-enable object
				object->SetVisible(true);
				object->SetActive(true);
				object->SetPosition(position);
				object->SetEulerAngles(eulerAngles);
				parent->AddChild(object);
			}
		}
		return std::static_pointer_cast<T>(object);
	}

	/**
	* Will put the object in stand-by mode, that's far off the camera, deactive and invisible.
	*/
	void Recycle(std::shared_ptr<Entity> object)
	{
		if (object)
		{
			// Make available again
			_pool[object] = true;
			// Detach from current parent
			auto parent = object->GetParent();
			if (parent)
				parent->DetachChild(object);
			// Set in stand-by
			object->SetVisible(false);
			object->SetActive(false);
			object->SetPosition(glm::vec3(9999.f));
		}
	}

private:
	std::unordered_map<std::shared_ptr<Entity>, bool> _pool; // Map containing all instanced objects. Key -> ptr to object. Value -> whereas or not object is available.
};

NS_VG_END

#endif // __VGOBJECTPOOL_H__
