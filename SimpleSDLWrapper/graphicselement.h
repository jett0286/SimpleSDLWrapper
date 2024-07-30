#pragma once

#include <string>

#include <SDL2/SDL_ttf.h>

#include "sprite.h"

class SSW_GraphicsElement_Base
{
	public:
		SSW_GraphicsElement_Base ();
		virtual void render (SDL_Renderer* sdlrenderer) = 0;
		
		void setDestRect (SDL_Rect destRect);
		void moveDestRect (int xPos, int yPos);
		
		void enable ();
		void disable ();
		void toggle ();

		void setPriority (int priority);
		int getPriority ();
	protected:
		SDL_Rect destRect_;
		bool isEnabled_;
		
		int priority_;
};

class SSW_GraphicsElement_Sprite : public SSW_GraphicsElement_Base
{
	public:
		SSW_GraphicsElement_Sprite ();
		SSW_GraphicsElement_Sprite (SSW_Sprite* pSprite);
		virtual void render (SDL_Renderer* sdlrenderer);
		void setSprite (SSW_Sprite* pSprite);
	private:
		SSW_Sprite* pSprite_;
};

class SSW_GraphicsElement_SolidColor : public SSW_GraphicsElement_Base
{
	public:
		SSW_GraphicsElement_SolidColor ();
		SSW_GraphicsElement_SolidColor (SDL_Color renderColor);
		virtual void render (SDL_Renderer* sdlrenderer);
		void setColor (SDL_Color renderColor);
	private:
		SDL_Color renderColor_;
};

class SSW_GraphicsElement_TTF : public SSW_GraphicsElement_Base
{
	public:
		SSW_GraphicsElement_TTF ();
		SSW_GraphicsElement_TTF (TTF_Font*, std::string, SDL_Color textColor);
		~SSW_GraphicsElement_TTF ();
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