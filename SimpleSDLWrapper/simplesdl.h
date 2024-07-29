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
		
		void mapKey (SDL_Keycode, SSW_Command*);
		void unmapKey (SDL_Keycode);
		void remapKey (SDL_Keycode src, SDL_Keycode dest);
		void handleInput ();

		void registerGraphicsElement (SSW_GraphicsElement* graphicsElement);
		void registerGraphicsElementFront (SSW_GraphicsElement* graphicsElement);
		void registerMouseElement (MouseElement* mouseElement);
		void registerMouseElementFront (MouseElement* mouseElement);

	private:
		SSW_InputManager inputMan_;
		SSW_GraphicsManager graphicsMan_;
};