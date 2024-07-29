#include "sprite.h"

SSW_Sprite::SSW_Sprite (SDL_Texture* pSpritesheet, int spritesheetXPos, int spritesheetYPos, int spriteWidth, int spriteHeight)
{
	pSpritesheet_ = pSpritesheet;
	
	srcRect_.x = spritesheetXPos;
	srcRect_.y = spritesheetYPos;
	srcRect_.w = spriteWidth;
	srcRect_.h = spriteHeight;
}

bool SSW_Sprite::render (SDL_Renderer* pRenderer, SDL_Rect* pDestRect)
{
	SDL_RenderCopy (pRenderer, pSpritesheet_, &srcRect_, pDestRect);
	return true; // If it doesn't return, something's wrong anyway lol
}

//void Sprite::setSpritesheet (SDL_Texture* pSpritesheet)
//{
//	pSpritesheet_ = pSpritesheet;
//}

//void Sprite::setSrcRect (int x, int y, int w, int h)
//{
//	srcRect
//}
