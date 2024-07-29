#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

#include "sprite.h"

class SSW_GraphicsElement
{
	public:
		SSW_GraphicsElement ();
		virtual void render (SDL_Renderer* sdlrenderer) = 0;
		void setDestRect (SDL_Rect destRect);
		// likely to be removed
		void moveDestRect (int xPos, int yPos);
		void enable ();
		void disable ();
		void toggle ();

	protected:
		SDL_Rect destRect_;
		bool isEnabled_;
};

class SpriteGraphicsElement : public SSW_GraphicsElement
{
	public:
		SpriteGraphicsElement ();
		SpriteGraphicsElement (SSW_Sprite* pSprite);
		virtual void render (SDL_Renderer* sdlrenderer);
		void setSprite (SSW_Sprite* pSprite);
	private:
		SSW_Sprite* pSprite_;
};

class SolidColorGraphicsElement : public SSW_GraphicsElement
{
	public:
		SolidColorGraphicsElement ();
		SolidColorGraphicsElement (SDL_Color renderColor);
		virtual void render (SDL_Renderer* sdlrenderer);
		void setColor (SDL_Color renderColor);
	private:
		SDL_Color renderColor_;
};

class TTFGraphicsElement : public SSW_GraphicsElement
{
	public:
		TTFGraphicsElement ();
		TTFGraphicsElement (TTF_Font*, std::string, SDL_Color textColor);
		~TTFGraphicsElement ();
		virtual void render (SDL_Renderer* sdlrenderer);
		void setBodyText (std::string bodyText);
		void setTTFFont (TTF_Font* ttfFont);
		void setTextColor (SDL_Color textColor);
	private:
		void updateTexture (SDL_Renderer* sdlrenderer);

		std::string bodyText_;
		TTF_Font* ttfFont_;
		SDL_Color textColor_;

		bool textureNeedsUpdate_;
		SDL_Texture* sdltexture_;
};