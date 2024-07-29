#pragma once

#include <SDL2/SDL.h>

#include "command.h"

class SSW_MouseElement
{
	public:
		SSW_MouseElement ();
		SSW_MouseElement (SDL_Rect clickableRect, SSW_Command_Base* onLeftClick, SSW_Command_Base* onLeftUnclick, SSW_Command_Base* onRightClick, SSW_Command_Base* onRightUnclick, SSW_Command_Base* onHover, SSW_Command_Base* onMouseMove);
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
		void setOnLeftClick (SSW_Command_Base* onLeftClick);
		void setOnLeftUnclick (SSW_Command_Base* onLeftUnclick);
		void setOnRightClick (SSW_Command_Base* onRightClick);
		void setOnRightUnclick (SSW_Command_Base* onRightUnclick);
		void setOnHover (SSW_Command_Base* onHover);
		void setOnMouseMove (SSW_Command_Base* onMouseMove);

		void setPriority (int priority);
		int getPriority ();
	protected:
		SDL_Rect clickableRect_;
		SSW_Command_Base* onLeftClick_;
		SSW_Command_Base* onLeftUnclick_;
		SSW_Command_Base* onRightClick_;
		SSW_Command_Base* onRightUnclick_;
		SSW_Command_Base* onHover_;
		SSW_Command_Base* onMouseMove_;

		bool isHovering_;
		bool isEnabled_;

		int priority_; // higher is front-er
};
