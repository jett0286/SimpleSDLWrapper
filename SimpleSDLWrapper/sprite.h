#pragma once

#include <SDL2/SDL.h>

class SSW_Sprite
{
	public:
		SSW_Sprite(SDL_Texture* pSpritesheet, int spritesheetXPos, int spritesheetYPos, int spriteWidth, int spriteHeight);
		bool render (SDL_Renderer* pRenderer, SDL_Rect* pDestRect);
	private:
		SDL_Texture* pSpritesheet_;
		SDL_Rect srcRect_;
};