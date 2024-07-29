#include "mouseelement.h"

MouseElement::MouseElement ()
{
	clickableRect_ = {0, 0, 0, 0};
	onLeftClick_ = NULL;
	onLeftUnclick_ = NULL;
	onRightClick_ = NULL;
	onRightUnclick_ = NULL;
	onHover_ = NULL;
	onMouseMove_ = NULL;
	isHovering_ = false;
	isEnabled_ = true;
}

MouseElement::MouseElement (SDL_Rect clickableRect = {0, 0, 0, 0}, SSW_Command* onLeftClick = NULL, SSW_Command* onLeftUnclick = NULL, 
														SSW_Command* onRightClick = NULL, SSW_Command* onRightUnclick = NULL, SSW_Command* onHover = NULL, SSW_Command* onMouseMove = NULL)
{
	clickableRect_ = clickableRect;
	onLeftClick_ = onLeftClick;
	onLeftUnclick_ = onLeftUnclick;
	onRightClick_ = onRightClick;
	onRightUnclick_ = onRightUnclick;
	onHover_ = onHover;
	onMouseMove_ = onMouseMove;
	isHovering_ = false;
	isEnabled_ = true;
	
}

void MouseElement::executeLeftClick ()
{
	if (isEnabled_ && onLeftClick_ != NULL)
	{
		onLeftClick_->execute ();
	}
}

void MouseElement::executeLeftUnclick ()
{
	if (isEnabled_ && onLeftUnclick_ != NULL)
	{
		onLeftUnclick_->execute ();
	}
}

void MouseElement::executeRightClick ()
{
	if (isEnabled_ && onRightClick_ != NULL)
	{
		onRightClick_->execute ();
	}
}

void MouseElement::executeRightUnclick ()
{
	if (isEnabled_ && onRightUnclick_ != NULL)
	{
		onRightUnclick_->execute ();
	}
}

void MouseElement::checkAndExecuteHover ()
{
	if (isEnabled_ && !isHovering_ && onHover_ != NULL)
	{
		onHover_->execute ();
		isHovering_ = true;
	}
}

void MouseElement::checkAndExecuteUnhover ()
{
	if (isEnabled_ && isHovering_ && onHover_ != NULL)
	{
		onHover_->undo ();
		isHovering_ = false;
	}
}

void MouseElement::executeMouseMove ()
{
	if (isEnabled_ && onMouseMove_ != NULL)
	{
		onMouseMove_->execute ();
	}
}

void MouseElement::enable ()
{
	isEnabled_ = true;
}

void MouseElement::disable ()
{
	isEnabled_ = false;
}

void MouseElement::toggle ()
{
	isEnabled_ = !isEnabled_;
}

bool MouseElement::intersects (int xPos, int yPos) const
{
	SDL_Point mousePos = {xPos, yPos};
	if (SDL_PointInRect (&mousePos, &clickableRect_))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MouseElement::getIsHovering ()
{
	return isHovering_;
}

void MouseElement::setClickableRect (SDL_Rect clickableRect)
{
	clickableRect_ = clickableRect;
}

void MouseElement::moveClickableRect (int xPos, int yPos)
{
	clickableRect_.x = xPos;
	clickableRect_.y = yPos;
}

void MouseElement::setOnLeftClick (SSW_Command* onClick)
{
	onLeftClick_ = onClick;
}

void MouseElement::setOnLeftUnclick (SSW_Command* onUnclick)
{
	onLeftUnclick_ = onUnclick;
}

void MouseElement::setOnRightClick (SSW_Command* onRightClick)
{
	onRightClick_ = onRightClick;
}

void MouseElement::setOnRightUnclick (SSW_Command* onRightUnclick)
{
	onRightUnclick_ = onRightUnclick;
}

void MouseElement::setOnHover (SSW_Command* onHover)
{
	onHover_ = onHover;
}

void MouseElement::setOnMouseMove (SSW_Command* onMouseMove)
{
	onMouseMove_ = onMouseMove;
}
