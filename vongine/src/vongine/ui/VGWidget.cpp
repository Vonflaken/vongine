#include "VGWidget.h"
#include "base/VGCoreManager.h"
#include "ui/VGUIMessages.h"
#include "ui/VGUIManager.h"
#include "ui/VGUICanvas.h"
#include "rendering/VGCamera.h"

#include <algorithm>

NS_VG_BEGIN

namespace ui
{
	/**
	* Comparison function for sorting Widgets based on order property.
	* DESC order.
	*/
	inline bool WidgetOrderComp(const std::shared_ptr<Widget> first, const std::shared_ptr<Widget> last)
	{
		return first->GetOrder() > last->GetOrder();
	}

	/**********************************************************************************************************/
	/********************* Util types definitions for UI positioning ******************************************/

	float Widget::UIRelative::XPercentFrom(const UIxAnchor anchor, const float width, const float percentOffset)
	{
		// Get inital offset
		float offset = width * percentOffset;

		// If anchor is right the offset is flipped
		if (anchor == UIxAnchor::RIGHT)
		{
			offset = -offset;
		}
		return offset;
	}

	float Widget::UIRelative::YPercentFrom(const UIyAnchor anchor, const float height, const float percentOffset)
	{
		// Get initial offset
		float offset = height * percentOffset;

		// If anchor is bottom the offset is flipped
		if (anchor == UIyAnchor::BOTTOM)
		{
			offset = -offset;
		}
		return offset;
	}

	float Widget::UIRelative::XPercentTo(const UIxAnchor anchor, const float width, const float offset)
	{
		float percentOffset = 0.f;
		if (width != 0.f)
		{
			// Get initial percentage
			percentOffset = offset / width;

			// If anchor is right the percentage is flipped
			if (anchor == UIxAnchor::RIGHT)
			{
				percentOffset = -percentOffset;
			}
		}
		return percentOffset;
	}

	float Widget::UIRelative::YPercentTo(const UIyAnchor anchor, const float height, const float offset)
	{
		float percentOffset = 0.f;
		if (height != 0.f)
		{
			// Get initial percentage
			percentOffset = offset / height;

			// If anchor is bottom the percentage is flipped
			if (anchor == UIyAnchor::BOTTOM)
			{
				percentOffset = -percentOffset;
			}
		}
		return percentOffset;
	}
		  
	float Widget::UIRelative::XAnchorAdjustment(const UIxAnchor anchor, const float width, const UIxAnchor originAnchor)
	{
		float adjustment = 0.f;
		switch (anchor)
		{
		case UIxAnchor::LEFT:
		{
			if (originAnchor == UIxAnchor::CENTER)
			{
				adjustment -= width / 2.f;
			}
			else if (originAnchor == UIxAnchor::RIGHT)
			{
				adjustment -= width;
			}
			break;
		}
		case UIxAnchor::RIGHT:
		{
			if (originAnchor == UIxAnchor::LEFT)
			{
				adjustment += width;
			}
			else if (originAnchor == UIxAnchor::CENTER)
			{
				adjustment += width / 2.f;
			}
			break;
		}
		case UIxAnchor::CENTER:
		{
			if (originAnchor == UIxAnchor::LEFT)
			{
				adjustment += width / 2.f;
			}
			else if (originAnchor == UIxAnchor::RIGHT)
			{
				adjustment -= width / 2.f;
			}
			break;
		}
		}

		return adjustment;
	}

	float Widget::UIRelative::YAnchorAdjustment(const UIyAnchor anchor, const float height, const UIyAnchor originAnchor)
	{
		float adjustment = 0.f;
		switch (anchor)
		{
		case UIyAnchor::TOP:
			if (originAnchor == UIyAnchor::CENTER)
			{
				adjustment -= height / 2.f;
			}
			else if (originAnchor == UIyAnchor::BOTTOM)
			{
				adjustment -= height;
			}
			break;
		case UIyAnchor::BOTTOM:
			if (originAnchor == UIyAnchor::TOP)
			{
				adjustment += height;
			}
			else if (originAnchor == UIyAnchor::CENTER)
			{
				adjustment += height / 2.f;
			}
			break;
		case UIyAnchor::CENTER:
			if (originAnchor == UIyAnchor::TOP)
			{
				adjustment += height / 2.f;
			}
			else if (originAnchor == UIyAnchor::BOTTOM)
			{
				adjustment -= height / 2.f;
			}
			break;
		}
		return adjustment;
	}
	/************* End util types definitions for UI positioning **************************************************/
	/**************************************************************************************************************/


	/**************************************************************************************************************/
	/*************************************** Positioning methods definitions **************************************/

	void Widget::PositionFromCenter(const float percentFromTop, const float percentFromLeft)
	{
		PositionFromCenter(percentFromTop, percentFromLeft, UIyAnchor::CENTER, UIxAnchor::CENTER);
	}

	void Widget::PositionFromTopLeft(const float percentFromTop, const float percentFromLeft)
	{
		PositionFromTopLeft(percentFromTop, percentFromLeft, UIyAnchor::TOP, UIxAnchor::LEFT);
	}

	void Widget::PositionFromTopRight(const float percentFromTop, const float percentFromRight)
	{
		PositionFromTopRight(percentFromTop, percentFromRight, UIyAnchor::TOP, UIxAnchor::RIGHT);
	}

	void Widget::PositionFromBottomLeft(const float percentFromBottom, const float percentFromLeft)
	{
		PositionFromBottomLeft(percentFromBottom, percentFromLeft, UIyAnchor::BOTTOM, UIxAnchor::LEFT);
	}

	void Widget::PositionFromBottomRight(const float percentFromBottom, const float percentFromRight)
	{
		PositionFromBottomRight(percentFromBottom, percentFromRight, UIyAnchor::BOTTOM, UIxAnchor::RIGHT);
	}

	void Widget::PositionFromTop(const float percentFromTop)
	{
		PositionFromTop(percentFromTop, 0.f, UIyAnchor::TOP, UIxAnchor::CENTER);
	}

	void Widget::PositionFromTop(const float percentFromTop, const float percentFromLeft)
	{
		PositionFromTop(percentFromTop, percentFromLeft, UIyAnchor::TOP, UIxAnchor::CENTER);
	}

	void Widget::PositionFromBottom(const float percentFromBottom)
	{
		PositionFromBottom(percentFromBottom, 0.f, UIyAnchor::BOTTOM, UIxAnchor::CENTER);
	}

	void Widget::PositionFromBottom(const float percentFromBottom, const float percentFromLeft)
	{
		PositionFromBottom(percentFromBottom, percentFromLeft, UIyAnchor::BOTTOM, UIxAnchor::CENTER);
	}

	void Widget::PositionFromLeft(const float percentFromLeft)
	{
		PositionFromLeft(0.f, percentFromLeft, UIyAnchor::CENTER, UIxAnchor::LEFT);
	}

	void Widget::PositionFromLeft(const float percentFromTop, const float percentFromLeft)
	{
		PositionFromLeft(percentFromTop, percentFromLeft, UIyAnchor::CENTER, UIxAnchor::LEFT);
	}

	void Widget::PositionFromRight(const float percentFromRight)
	{
		PositionFromRight(0.f, percentFromRight, UIyAnchor::CENTER, UIxAnchor::RIGHT);
	}

	void Widget::PositionFromRight(const float percentFromTop, const float percentFromRight)
	{
		PositionFromRight(percentFromTop, percentFromRight, UIyAnchor::CENTER, UIxAnchor::RIGHT);
	}

	void Widget::RefreshPosition()
	{
		// Get parent anchor position
		Point pos = ParentAnchorPosition();

		// Add position offset
		if (_anchorInfo.uiPrecision == UIPrecision::PERCENTAGE)
		{
			pos.x += UIRelative::XPercentFrom(_anchorInfo.uiXAnchor, (float)ParentWidth(), _anchorInfo.offsetX);
			pos.y += UIRelative::YPercentFrom(_anchorInfo.uiYAnchor, (float)ParentHeight(), _anchorInfo.offsetY);
		}

		// Adjust for anchor offset
		pos.x -= UIRelative::XAnchorAdjustment(_anchorInfo.uiXAnchor, (float)_size.width, _anchorInfo.originUIxAnchor);
		pos.x += UIRelative::YAnchorAdjustment(_anchorInfo.uiYAnchor, (float)_size.height, _anchorInfo.originUIyAnchor);

		// Set new position
		SetPosition(pos.x, pos.y);
	}

	void Widget::PositionFromCenter(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::CENTER;
		_anchorInfo.parentUIyAnchor = UIyAnchor::CENTER;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromLeft;
		_anchorInfo.offsetY = percentFromTop;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromTopLeft(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::LEFT;
		_anchorInfo.parentUIyAnchor = UIyAnchor::TOP;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromLeft;
		_anchorInfo.offsetY = percentFromTop;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromTopRight(const float percentFromTop, const float percentFromRight, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::RIGHT;
		_anchorInfo.parentUIyAnchor = UIyAnchor::TOP;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromRight;
		_anchorInfo.offsetY = percentFromTop;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromBottomLeft(const float percentFromBottom, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::LEFT;
		_anchorInfo.parentUIyAnchor = UIyAnchor::BOTTOM;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromLeft;
		_anchorInfo.offsetY = percentFromBottom;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromBottomRight(const float percentFromBottom, const float percentFromRight, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::RIGHT;
		_anchorInfo.parentUIyAnchor = UIyAnchor::BOTTOM;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromRight;
		_anchorInfo.offsetY = percentFromBottom;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromLeft(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::LEFT;
		_anchorInfo.parentUIyAnchor = UIyAnchor::CENTER;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromLeft;
		_anchorInfo.offsetY = percentFromTop;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromTop(const float percentFromTop, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::CENTER;
		_anchorInfo.parentUIyAnchor = UIyAnchor::TOP;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromLeft;
		_anchorInfo.offsetY = percentFromTop;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromBottom(const float percentFromBottom, const float percentFromLeft, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::CENTER;
		_anchorInfo.parentUIyAnchor = UIyAnchor::BOTTOM;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromLeft;
		_anchorInfo.offsetY = percentFromBottom;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	void Widget::PositionFromRight(const float percentFromTop, const float percentFromRight, const UIyAnchor yAnchor, const UIxAnchor xAnchor)
	{
		// Update anchor information
		_anchorInfo.parentUIxAnchor = UIxAnchor::RIGHT;
		_anchorInfo.parentUIyAnchor = UIyAnchor::CENTER;
		_anchorInfo.uiXAnchor = xAnchor;
		_anchorInfo.uiYAnchor = yAnchor;
		_anchorInfo.offsetX = percentFromRight;
		_anchorInfo.offsetY = percentFromTop;
		_anchorInfo.uiPrecision = UIPrecision::PERCENTAGE;

		// Refresh position
		RefreshPosition();
	}

	Point Widget::ParentAnchorPosition() const
	{
		Point pos;
		uint32 width, height;
		UIxAnchor originUIxAnchor = UIxAnchor::LEFT;
		UIyAnchor originUIyAnchor = UIyAnchor::TOP;
		// Determine correct parent values
		if (auto parent = _anchorInfo.parentWidget.lock())
		{
			glm::vec3 parentPos = parent->GetPosition();
			Size parentSize = parent->GetSize();
			pos = { parentPos.x, parentPos.y };
			width = parentSize.width;
			height = parentSize.width;
		}
		else
		{
			// Try current Canvas
			Canvas* canvas = UIManager::GetInstance().GetRootWidget();
			if (canvas)
			{
				glm::vec3 canvasPos = canvas->GetPosition();
				Size canvasSize = canvas->GetSize();
				pos = { canvasPos.x, canvasPos.y };
				width = canvasSize.width;
				height = canvasSize.height;
			}
			else
			{
				// Fallback screen size
				Size screenSize = CoreManager::GetInstance().GetScreenSize();
				pos = { 0.f, 0.f };
				width = screenSize.width;
				height = screenSize.height;
			}
		}

		// Adjust anchor offset
		pos.x += UIRelative::XAnchorAdjustment(_anchorInfo.parentUIxAnchor, (float)width, originUIxAnchor);
		pos.y -= UIRelative::YAnchorAdjustment(_anchorInfo.parentUIyAnchor, (float)height, originUIyAnchor);

		return pos;
	}

	uint32 Widget::ParentWidth() const
	{
		uint32 width;
		if (_anchorInfo.parentWidget.expired())
		{
			Canvas* canvas = UIManager::GetInstance().GetRootWidget();
			if (canvas)
			{
				width = canvas->GetSize().width;
			}
			else
			{
				width = CoreManager::GetInstance().GetScreenSize().width;
			}
		}
		else
		{
			width = _anchorInfo.parentWidget.lock()->GetSize().width;
		}
		return width;
	}

	uint32 Widget::ParentHeight() const
	{
		uint32 height;
		if (_anchorInfo.parentWidget.expired())
		{
			Canvas* canvas = UIManager::GetInstance().GetRootWidget();
			if (canvas)
			{
				height = canvas->GetSize().height;
			}
			else
			{
				height = CoreManager::GetInstance().GetScreenSize().height;
			}
		}
		else
		{
			height = _anchorInfo.parentWidget.lock()->GetSize().height;
		}
		return height;
	}
	/************************* End positioning methods definitions ************************************************/
	/**************************************************************************************************************/


	std::shared_ptr<Widget> Widget::Create()
	{
		return Widget::Create(glm::vec3(0.f, 0.f, 0.f), { 0, 0 });
	}

	std::shared_ptr<Widget> Widget::Create(const glm::vec3& position)
	{
		return Widget::Create(position, { 0, 0 });
	}

	std::shared_ptr<Widget> Widget::Create(const glm::vec3& position, const Size& size)
	{
		auto widget = std::make_shared<Widget>();
		if (widget->Init(position, size))
		{
			return widget;
		}

		return nullptr;
	}

	Widget::Widget()
	: _size(0, 0)
	, _order(0)
	, _anchorInfo(UIAnchorInfo::Default())
	{}

	bool Widget::Init(const glm::vec3& position, const Size& size)
	{
		if (Entity::Init(position))
		{
			SetSize(size);
			SetCameraTag(Camera::DEFAULT_CAMERA_UI);

			return true;
		}

		return false;
	}

	void Widget::SetSize(const Size& size)
	{
		_size = size;
	}

	void Widget::SetOrder(const int32 order)
	{
		_order = order;
	}

	void Widget::AddWidget(const std::shared_ptr<Widget> widget)
	{
		Entity::AddChild(widget);
	}

	void Widget::SetParent(const std::shared_ptr<Entity> parent)
	{
		Entity::SetParent(parent);

		_anchorInfo.parentWidget = std::static_pointer_cast<Widget>(parent);
	}

	void Widget::AddChild(const std::shared_ptr<Entity> entity) {}

	bool Widget::InjectMessage(const Message& message)
	{
		bool messageHandled = false;

		// Sort Widgets, higher orders go first
		std::sort(_children.begin(), _children.end(), WidgetOrderComp);
		// Search for a child that handles the message, from the most front to back
		for (uint32 i = 0; i < _children.size(); i++)
		{
			messageHandled = std::static_pointer_cast<Widget>(_children[i])->InjectMessage(message);
			if (messageHandled)
				break;
		}

		// If any child handled, maybe is for this widget.
		if (!messageHandled && IsVisible())
		{
			switch (message.type)
			{
			case MessageType::MouseButtonDown:
			{
				auto msgMouseBtnDown = static_cast<const MessageMouseButtonDown*>(&message);
				if (msgMouseBtnDown->buttonId == 0) // Only handles left button
				{
					if (IsPointInside(Point((float)msgMouseBtnDown->x, (float)msgMouseBtnDown->y)))
					{
						HandleMessage(message);
						messageHandled = true;
					}
				}
				break;
			}
			case MessageType::MouseButtonUp:
			{
				auto msgMouseBtnUp = static_cast<const MessageMouseButtonUp*>(&message);
				if (msgMouseBtnUp->buttonId == 0) // Only handles left button
				{
					if (IsPointInside(Point((float)msgMouseBtnUp->x, (float)msgMouseBtnUp->y)))
					{
						HandleMessage(message);
						messageHandled = true;
					}
				}
				break;
			}
			case MessageType::PointerMove:
			{
				auto msgPointerMove = static_cast<const MessagePointerMove*>(&message);
				if (IsPointInside(Point((float)msgPointerMove->x, (float)msgPointerMove->y)))
				{
					if (!s_hoveredWidget.expired())
					{
						// Notify old hovered Widget
						s_hoveredWidget.lock()->HandleMessage(MessagePointerHoverOut());
					}

					s_hoveredWidget = std::static_pointer_cast<Widget>(shared_from_this()); // Set this as new hovered Widget
					HandleMessage(MessagePointerHoverIn());
					messageHandled = true;
				}
				break;
			}
			}
		}
		return messageHandled;
	}

	Rect Widget::GetWidgetRect()
	{
		Point absolute2DPos = GetAbsolute2DPosition();
		// Set rect origin at bottom-left corner
		Size scaledSize((uint32)(_size.width * _scale.x), (uint32)(_size.height * _scale.y));
		absolute2DPos.x -= scaledSize.width / 2.f;
		absolute2DPos.y -= scaledSize.height / 2.f;
		return Rect(absolute2DPos.x, absolute2DPos.y, scaledSize.width, scaledSize.height);
	}

	bool Widget::IsPointInside(const Point& point)
	{
		Rect r = GetWidgetRect();
		return r.IsPointInside(point);
	}
}

NS_VG_END
