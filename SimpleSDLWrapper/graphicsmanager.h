#pragma once

#include <map>
#include <vector>
#include <string>

#include <SDL2/SDL_image.h>

#include "graphicselement.h"

class SSW_GraphicsManager
{
	public:
		~SSW_GraphicsManager ();
		bool init (int winHeight, int winWidth);
		void refresh ();

		void setBackgroundColor (SDL_Color backgroundColor);

		void registerGraphicsElement (SSW_GraphicsElement* graphicsElement);
		void registerGraphicsElementFront (SSW_GraphicsElement* graphicsElement);

		void loadSprites (const char* spritesheetPath, int spriteHeight, int spriteWidth);
		void unloadSprites ();
		SSW_Sprite* getSpriteFromID (int spriteID);

	private:
		bool initSDLWindow (int winWidth, int winHeight);
		bool initSDLRenderer ();
		bool initSDLImage ();
		bool initSDLTTF ();

		int winWidth_;
		int winHeight_;

		SDL_Window* sdlwindow_;
		SDL_Renderer* sdlrenderer_;
		SDL_Texture* spritesheet_;

		SDL_Color backgroundColor_;

		std::vector<SSW_GraphicsElement*> vectorGraphicsElements_;

		std::vector<SSW_Sprite*> vectorSpriteData_;
		std::map<std::string, SSW_Sprite*> mSpritesTable_;
};

