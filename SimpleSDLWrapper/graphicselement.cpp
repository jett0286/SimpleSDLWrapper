#include "graphicselement.h"

SSW_GraphicsElement::SSW_GraphicsElement ()
{
	destRect_ = {0, 0, 0, 0};
	isEnabled_ = true;
}

void SSW_GraphicsElement::setDestRect (SDL_Rect destRect)
{
	destRect_ = destRect;
}

void SSW_GraphicsElement::moveDestRect (int xPos, int yPos)
{
	destRect_.x = xPos;
	destRect_.y = yPos;
}

void SSW_GraphicsElement::enable ()
{
	isEnabled_ = true;
}

void SSW_GraphicsElement::disable ()
{
	isEnabled_ = false;
}

void SSW_GraphicsElement::toggle ()
{
	isEnabled_ = !isEnabled_;
}

SpriteGraphicsElement::SpriteGraphicsElement ()
{
	pSprite_ = NULL;
}

SpriteGraphicsElement::SpriteGraphicsElement (SSW_Sprite* pSprite)
: SSW_GraphicsElement () 
{
	pSprite_ = pSprite;
}

void SpriteGraphicsElement::render (SDL_Renderer* sdlrenderer)
{
	if (isEnabled_ && (pSprite_ != NULL))
	{
		pSprite_->render (sdlrenderer, &destRect_);
	}
}

void SpriteGraphicsElement::setSprite (SSW_Sprite* pSprite)
{
	pSprite_ = pSprite;
}

SolidColorGraphicsElement::SolidColorGraphicsElement ()
{
	renderColor_ = {0xFF, 0xFF, 0xFF, 0xFF};
}

SolidColorGraphicsElement::SolidColorGraphicsElement (SDL_Color renderColor)
: SSW_GraphicsElement ()
{
	renderColor_ = renderColor;
}

void SolidColorGraphicsElement::render (SDL_Renderer* sdlrenderer)
{
	if (isEnabled_)
	{
		SDL_SetRenderDrawColor (sdlrenderer, renderColor_.r, renderColor_.g, renderColor_.b, renderColor_.a);
		SDL_RenderFillRect (sdlrenderer, &destRect_);
		SDL_SetRenderDrawColor (sdlrenderer, 0x00, 0x00, 0x00, 0xFF); // REMOVE ME
		SDL_RenderDrawRect (sdlrenderer, &destRect_); // REMOVE ME
	}
}

void SolidColorGraphicsElement::setColor (SDL_Color renderColor)
{
	renderColor_ = renderColor;
}

TTFGraphicsElement::TTFGraphicsElement ()
{
	ttfFont_ = NULL;
	bodyText_ = "";
	textColor_ = {0x00, 0x00, 0x00, 0xFF};
	sdltexture_ = NULL;
	textureNeedsUpdate_ = true;
}

TTFGraphicsElement::TTFGraphicsElement (TTF_Font* ttfFont, std::string bodyText, SDL_Color textColor) 
	: SSW_GraphicsElement ()
{
	ttfFont_ = ttfFont;
	bodyText_ = bodyText;
	textColor_ = textColor;
	sdltexture_ = NULL;
	textureNeedsUpdate_ = true;
}

TTFGraphicsElement::~TTFGraphicsElement ()
{
	SDL_DestroyTexture (sdltexture_);
}

// RESIZING: Use same font every time? Or different fonts for different sizes?
// if resizing accesses the disk, that's crazy inefficient
void TTFGraphicsElement::render (SDL_Renderer* sdlrenderer)
{
	if (ttfFont_ != NULL && isEnabled_)
	{
		if (textureNeedsUpdate_)
		{
			updateTexture (sdlrenderer);
		}
		SDL_RenderCopy (sdlrenderer, sdltexture_, NULL, &destRect_);
	}
}

void TTFGraphicsElement::setBodyText (std::string bodyText)
{
	bodyText_ = bodyText;
	textureNeedsUpdate_ = true;
}

void TTFGraphicsElement::setTTFFont (TTF_Font* ttfFont)
{
	ttfFont_ = ttfFont;
	textureNeedsUpdate_ = true;
}

void TTFGraphicsElement::setTextColor (SDL_Color textColor)
{
	textColor_ = textColor;
	textureNeedsUpdate_ = true;
}

void TTFGraphicsElement::updateTexture (SDL_Renderer* sdlrenderer)
{
	SDL_Surface* textSurface = NULL;

	textSurface = TTF_RenderText_Blended_Wrapped (ttfFont_, bodyText_.c_str (), textColor_, destRect_.w);
	sdltexture_ = SDL_CreateTextureFromSurface (sdlrenderer, textSurface);
	destRect_.w = textSurface->w;
	destRect_.h = textSurface->h;

	textureNeedsUpdate_ = false;

	SDL_FreeSurface (textSurface);
}
