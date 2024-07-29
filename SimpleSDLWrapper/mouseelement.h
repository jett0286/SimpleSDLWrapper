#pragma once

#include <SDL2/SDL.h>

#include "command.h"

class MouseElement
{
	public:
		MouseElement ();
		MouseElement (SDL_Rect clickableRect, SSW_Command* onLeftClick, SSW_Command* onLeftUnclick, SSW_Command* onRightClick, SSW_Command* onRightUnclick, SSW_Command* onHover, SSW_Command* onMouseMove);
		void executeLeftClick ();
		void executeLeftUnclick ();
		void executeRightClick ();
		void executeRightUnclick ();
		void checkAndExecuteHover ();
		void checkAndExecuteUnhover ();
		void executeMouseMove ();

		void enable ();
		void disable ();
		void toggle ();

		bool intersects (int xPos, int yPos) const;
		bool getIsHovering ();

		void setClickableRect (SDL_Rect clickableRect);
		
		void moveClickableRect (int xPos, int yPos);
		void setOnLeftClick (SSW_Command* onLeftClick);
		void setOnLeftUnclick (SSW_Command* onLeftUnclick);
		void setOnRightClick (SSW_Command* onRightClick);
		void setOnRightUnclick (SSW_Command* onRightUnclick);
		void setOnHover (SSW_Command* onHover);
		void setOnMouseMove (SSW_Command* onMouseMove);
	protected:
		SDL_Rect clickableRect_;
		SSW_Command* onLeftClick_;
		SSW_Command* onLeftUnclick_;
		SSW_Command* onRightClick_;
		SSW_Command* onRightUnclick_;
		SSW_Command* onHover_;
		SSW_Command* onMouseMove_;

		bool isHovering_;
		bool isEnabled_;
};
