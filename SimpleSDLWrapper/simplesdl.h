#pragma once

#include "inputmanager.h"
#include "graphicsmanager.h"

class SSW_Window
{
	public:
		SSW_Window ();
		SSW_Window(int winHeight, int winWidth);
		
		void refresh ();
		
		void setBackgroundColor (SDL_Color backgroundColor);

		void loadSprites (const char* spritesheetPath, int spriteHeight, int spriteWidth);
		void unloadSprites ();

		SSW_Sprite* getSpriteFromID (int spriteID);
		
		void mapKey (SDL_Keycode, SSW_Command_Base*);
		void unmapKey (SDL_Keycode);
		void remapKey (SDL_Keycode src, SDL_Keycode dest);
		void handleInput ();

		void registerGraphicsElement (SSW_GraphicsElement_Base* graphicsElement);
		void registerMouseElement (SSW_MouseElement* mouseElement);

		void setFPS (int framesPerSecond);

		void startTimer ();
		void endTimerAndWait (); // rename me

	private:
		int framesPerSecond_;
		int ticksPerFrame_;
		Uint32 ticks_;

		SSW_InputManager inputMan_;
		SSW_GraphicsManager graphicsMan_;
};