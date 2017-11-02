#include "VGWidget.h"
#include "base/VGCoreManager.h"

NS_VG_BEGIN

namespace ui
{
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


	Widget::Widget()
	: _size(0, 0)
	, _order(0)
	, _anchorInfo(UIAnchorInfo::Default())
	{}

	void Widget::SetSize(const Size& size)
	{
		_size = size;
	}

	void Widget::SetOrder(const int32 order)
	{
		_order = order;
	}


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
			pos.x += UIRelative::XPercentFrom(_anchorInfo.uiXAnchor, ParentWidth(), _anchorInfo.offsetX);
			pos.y += UIRelative::YPercentFrom(_anchorInfo.uiYAnchor, ParentHeight(), _anchorInfo.offsetY);
		}

		// Adjust for anchor offset
		pos.x -= UIRelative::XAnchorAdjustment(_anchorInfo.uiXAnchor, _size.width, _anchorInfo.originUIxAnchor);
		pos.x += UIRelative::YAnchorAdjustment(_anchorInfo.uiYAnchor, _size.height, _anchorInfo.originUIyAnchor);

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
		float width, height;
		UIxAnchor originUIxAnchor = UIxAnchor::LEFT;
		UIyAnchor originUIyAnchor = UIyAnchor::TOP;
		// Determine correct parent values
		if (!_anchorInfo.parent)
		{
			pos = { 0.f, 0.f };
			Size screenSize = CoreManager::GetInstance().GetScreenSize();
			width = screenSize.width;
			height = screenSize.height;
		}
		else
		{
			glm::vec3 parentPos = _anchorInfo.parent->GetPosition();
			Size parentSize = _anchorInfo.parent->GetSize();
			pos.x = parentPos.x; 
			pos.y = parentPos.y;
			width = parentSize.width; 
			height = parentSize.width;
		}

		// Adjust anchor offset
		pos.x += UIRelative::XAnchorAdjustment(_anchorInfo.parentUIxAnchor, width, originUIxAnchor);
		pos.y -= UIRelative::YAnchorAdjustment(_anchorInfo.parentUIyAnchor, height, originUIyAnchor);

		return pos;
	}

	float Widget::ParentWidth() const
	{
		return (!_anchorInfo.parent) ? CoreManager::GetInstance().GetScreenSize().width : _anchorInfo.parent->GetSize().width;
	}

	float Widget::ParentHeight() const
	{
		return (!_anchorInfo.parent) ? CoreManager::GetInstance().GetScreenSize().height : _anchorInfo.parent->GetSize().height;
	}
	/************************* End positioning methods definitions ************************************************/
	/**************************************************************************************************************/
}

NS_VG_END
