#ifndef __VGWIDGET_H__
#define __VGWIDGET_H__

#include "VGMacros.h"
#include "base/VGEntity.h"
#include "base/VGTypes.h"

NS_VG_BEGIN

namespace ui
{
	struct Message;

	class DLLAPI Widget : public Entity
	{
	private:
		/**********************************************************************************************************/
		/********************* Util types definitions for UI positioning ******************************************/
		enum class UIxAnchor { LEFT, RIGHT, CENTER };
		enum class UIyAnchor { TOP, BOTTOM, CENTER };
		enum class UIPrecision { PERCENTAGE, PIXEL }; // WARNING: Pixel precision not supported yet

		/**
		* Holds information about positioning anchors.
		*/
		struct UIAnchorInfo
		{
			/**
			* Creates a default anchor info object anchores to top left corner.
			*/
			static UIAnchorInfo Default()
			{
				return { std::weak_ptr<Widget>(), UIxAnchor::LEFT, UIyAnchor::TOP, UIxAnchor::LEFT, UIyAnchor::TOP, UIxAnchor::LEFT, UIyAnchor::BOTTOM, UIPrecision::PERCENTAGE, 0.f, 0.f };
			}

			std::weak_ptr<Widget> parentWidget;
			UIxAnchor parentUIxAnchor;
			UIyAnchor parentUIyAnchor;
			UIxAnchor uiXAnchor;
			UIyAnchor uiYAnchor;
			UIxAnchor originUIxAnchor;
			UIyAnchor originUIyAnchor;
			UIPrecision uiPrecision;
			float offsetX;
			float offsetY;
		};

		struct UIRelative
		{
			/**
			* Calculates offset based on window width percentage.
			*/
			static float XPercentFrom(const UIxAnchor anchor, const float width, const float percentOffset);
			/**
			* Calculates offset based on window height percentage.
			*/
			static float YPercentFrom(const UIyAnchor anchor, const float height, const float percentOffset);
			/**
			* Calculates window width percentage based on offset.
			*/
			static float XPercentTo(const UIxAnchor anchor, const float width, const float offset);
			/**
			* Calculates window height percentage based on offset.
			*/
			static float YPercentTo(const UIyAnchor anchor, const float height, const float offset);

			/**
			* Finds horizontal adjustment for anchor, based on width and origin of widget.
			*/
			static float XAnchorAdjustment(const UIxAnchor anchor, const float width, const UIxAnchor originAnchor);
			/**
			* Finds vertical adjustment for anchor, based on height and origin of widget.
			*/
			static float YAnchorAdjustment(const UIyAnchor anchor, const float height, const UIyAnchor originAnchor);
		};
		/************* End util types definitions for UI positioning **************************************************/
		/**************************************************************************************************************/


		/**************************************************************************************************************/
		/*************************************** Positioning methods definitions **************************************/
	public:
		void PositionFromCenter(const float percentFromTop, const float percentFromLeft);
		void PositionFromTopLeft(const float percentFromTop, const float percentFromLeft);
		void PositionFromTopRight(const float percentFromTop, const float percentFromRight);
		void PositionFromBottomLeft(const float percentFromBottom, const float percentFromLeft);
		void PositionFromBottomRight(const float percentFromBottom, const float percentFromRight);
		void PositionFromTop(const float percentFromTop);
		void PositionFromTop(const float percentFromTop, const float percentFromLeft);
		void PositionFromBottom(const float percentFromBottom);
		void PositionFromBottom(const float percentFromBottom, const float percentFromLeft);
		void PositionFromLeft(const float percentFromLeft);
		void PositionFromLeft(const float percentFromTop, const float percentFromLeft);
		void PositionFromRight(const float percentFromRight);
		void PositionFromRight(const float percentFromTop, const float percentFromRight);

	private:
		void RefreshPosition();
		void PositionFromCenter(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromTopLeft(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromTopRight(const float percentFromTop, const float percentFromRight, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromBottomLeft(const float percentFromBottom, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromBottomRight(const float percentFromBottom, const float percentFromRight, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromLeft(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromTop(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromBottom(const float percentFromBottom, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		void PositionFromRight(const float percentFromTop, const float percentFromRight, const UIyAnchor yAnchor, const UIxAnchor xAnchor);
		Point ParentAnchorPosition() const;

		uint32 ParentWidth() const;
		uint32 ParentHeight() const;
		/************************* End positioning methods definitions ************************************************/
		/**************************************************************************************************************/


	public:
		static std::shared_ptr<Widget> Create();
		static std::shared_ptr<Widget> Create(const glm::vec3& position);
		static std::shared_ptr<Widget> Create(const glm::vec3& position, const Size& size);

		Widget();

		using Entity::Init;
		virtual bool Init(const glm::vec3& position, const Size& size);

		void SetSize(const Size& size);
		const Size& GetSize() const { return _size; }

		/**
		* Sets draw order. Also used for the order at capturing events.
		*/
		void SetOrder(const int32 order);
		int32 GetOrder() const { return _order; }

		void AddWidget(const std::shared_ptr<Widget> widget);
		void SetParent(const std::shared_ptr<Entity> parent) override;

		/**
		* Does nothing in order to don't allow public set not-UI objects as child.
		*/
		void AddChild(const std::shared_ptr<Entity> entity) override;

		bool InjectMessage(const Message& message);
		/**
		* @return bool Whereas or not Widget handled the message.
		*/
		virtual void HandleMessage(const Message& message) {}

		/**
		* Returns a rectangle representing the Widget surface.
		* Rect origin at bottom-left.
		*/
		Rect GetWidgetRect();

		bool IsPointInside(const Point& point);

	protected:
		static std::weak_ptr<Widget> s_hoveredWidget; // Weak ref to the Widget that is currently being hovered by pointer. FIXME: Not quite happy with this solution for dispatching "pointer in/out hovering a Widget" event.

		int32 _order; // Draw order inside canvas, lower is draw first. Also used for the order at capturing events.
		Size _size;

	private:
		UIAnchorInfo _anchorInfo;
	};
}

NS_VG_END

#endif // __VGWIDGET_H__
