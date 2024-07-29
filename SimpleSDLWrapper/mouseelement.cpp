#include "mouseelement.h"

SSW_MouseElement::SSW_MouseElement ()
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

SSW_MouseElement::SSW_MouseElement (SDL_Rect clickableRect = {0, 0, 0, 0}, SSW_Command_Base* onLeftClick = NULL, SSW_Command_Base* onLeftUnclick = NULL, 
														SSW_Command_Base* onRightClick = NULL, SSW_Command_Base* onRightUnclick = NULL, SSW_Command_Base* onHover = NULL, SSW_Command_Base* onMouseMove = NULL)
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

void SSW_MouseElement::executeLeftClick ()
{
	if (isEnabled_ && onLeftClick_ != NULL)
	{
		onLeftClick_->execute ();
	}
}

void SSW_MouseElement::executeLeftUnclick ()
{
	if (isEnabled_ && onLeftUnclick_ != NULL)
	{
		onLeftUnclick_->execute ();
	}
}

void SSW_MouseElement::executeRightClick ()
{
	if (isEnabled_ && onRightClick_ != NULL)
	{
		onRightClick_->execute ();
	}
}

void SSW_MouseElement::executeRightUnclick ()
{
	if (isEnabled_ && onRightUnclick_ != NULL)
	{
		onRightUnclick_->execute ();
	}
}

void SSW_MouseElement::checkAndExecuteHover ()
{
	if (isEnabled_ && !isHovering_ && onHover_ != NULL)
	{
		onHover_->execute ();
		isHovering_ = true;
	}
}

void SSW_MouseElement::checkAndExecuteUnhover ()
{
	if (isEnabled_ && isHovering_ && onHover_ != NULL)
	{
		onHover_->undo ();
		isHovering_ = false;
	}
}

void SSW_MouseElement::executeMouseMove ()
{
	if (isEnabled_ && onMouseMove_ != NULL)
	{
		onMouseMove_->execute ();
	}
}

void SSW_MouseElement::enable ()
{
	isEnabled_ = true;
}

void SSW_MouseElement::disable ()
{
	isEnabled_ = false;
}

void SSW_MouseElement::toggle ()
{
	isEnabled_ = !isEnabled_;
}

bool SSW_MouseElement::intersects (int xPos, int yPos) const
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

bool SSW_MouseElement::getIsHovering ()
{
	return isHovering_;
}

void SSW_MouseElement::setClickableRect (SDL_Rect clickableRect)
{
	clickableRect_ = clickableRect;
}

void SSW_MouseElement::moveClickableRect (int xPos, int yPos)
{
	clickableRect_.x = xPos;
	clickableRect_.y = yPos;
}

void SSW_MouseElement::setOnLeftClick (SSW_Command_Base* onClick)
{
	onLeftClick_ = onClick;
}

void SSW_MouseElement::setOnLeftUnclick (SSW_Command_Base* onUnclick)
{
	onLeftUnclick_ = onUnclick;
}

void SSW_MouseElement::setOnRightClick (SSW_Command_Base* onRightClick)
{
	onRightClick_ = onRightClick;
}

void SSW_MouseElement::setOnRightUnclick (SSW_Command_Base* onRightUnclick)
{
	onRightUnclick_ = onRightUnclick;
}

void SSW_MouseElement::setOnHover (SSW_Command_Base* onHover)
{
	onHover_ = onHover;
}

void SSW_MouseElement::setOnMouseMove (SSW_Command_Base* onMouseMove)
{
	onMouseMove_ = onMouseMove;
}
