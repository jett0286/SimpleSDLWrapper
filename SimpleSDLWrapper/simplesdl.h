// TO BE RENAMED
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

	private:
		SSW_InputManager inputMan_;
		SSW_GraphicsManager graphicsMan_;
};