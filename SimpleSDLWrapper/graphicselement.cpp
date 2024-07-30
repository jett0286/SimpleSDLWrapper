#include "graphicselement.h"

SSW_GraphicsElement_Base::SSW_GraphicsElement_Base ()
{
	destRect_ = {0, 0, 0, 0};
	isEnabled_ = true;
	priority_ = 0;
}

void SSW_GraphicsElement_Base::setDestRect (SDL_Rect destRect)
{
	destRect_ = destRect;
}

void SSW_GraphicsElement_Base::moveDestRect (int xPos, int yPos)
{
	destRect_.x = xPos;
	destRect_.y = yPos;
}

void SSW_GraphicsElement_Base::enable ()
{
	isEnabled_ = true;
}

void SSW_GraphicsElement_Base::disable ()
{
	isEnabled_ = false;
}

void SSW_GraphicsElement_Base::toggle ()
{
	isEnabled_ = !isEnabled_;
}

void SSW_GraphicsElement_Base::setPriority (int priority)
{
	priority_ = priority;
}

int SSW_GraphicsElement_Base::getPriority ()
{
	return priority_;
}

SSW_GraphicsElement_Sprite::SSW_GraphicsElement_Sprite ()
{
	pSprite_ = NULL;
}

SSW_GraphicsElement_Sprite::SSW_GraphicsElement_Sprite (SSW_Sprite* pSprite)
: SSW_GraphicsElement_Base () 
{
	pSprite_ = pSprite;
}

void SSW_GraphicsElement_Sprite::render (SDL_Renderer* sdlrenderer)
{
	if (isEnabled_ && (pSprite_ != NULL))
	{
		pSprite_->render (sdlrenderer, &destRect_);
	}
}

void SSW_GraphicsElement_Sprite::setSprite (SSW_Sprite* pSprite)
{
	pSprite_ = pSprite;
}

SSW_GraphicsElement_SolidColor::SSW_GraphicsElement_SolidColor ()
{
	renderColor_ = {0xFF, 0xFF, 0xFF, 0xFF};
}

SSW_GraphicsElement_SolidColor::SSW_GraphicsElement_SolidColor (SDL_Color renderColor)
: SSW_GraphicsElement_Base ()
{
	renderColor_ = renderColor;
}

void SSW_GraphicsElement_SolidColor::render (SDL_Renderer* sdlrenderer)
{
	if (isEnabled_)
	{
		SDL_SetRenderDrawColor (sdlrenderer, renderColor_.r, renderColor_.g, renderColor_.b, renderColor_.a);
		SDL_RenderFillRect (sdlrenderer, &destRect_);
	}
}

void SSW_GraphicsElement_SolidColor::setColor (SDL_Color renderColor)
{
	renderColor_ = renderColor;
}

SSW_GraphicsElement_TTF::SSW_GraphicsElement_TTF ()
{
	ttfFont_ = NULL;
	bodyText_ = "";
	textColor_ = {0x00, 0x00, 0x00, 0xFF};
	sdltexture_ = NULL;
	textureNeedsUpdate_ = true;
}

SSW_GraphicsElement_TTF::SSW_GraphicsElement_TTF (TTF_Font* ttfFont, std::string bodyText, SDL_Color textColor) 
	: SSW_GraphicsElement_Base ()
{
	ttfFont_ = ttfFont;
	bodyText_ = bodyText;
	textColor_ = textColor;
	sdltexture_ = NULL;
	textureNeedsUpdate_ = true;
}

SSW_GraphicsElement_TTF::~SSW_GraphicsElement_TTF ()
{
	SDL_DestroyTexture (sdltexture_);
}

// RESIZING: Use same font every time? Or different fonts for different sizes?
// if resizing accesses the disk, that's crazy inefficient
void SSW_GraphicsElement_TTF::render (SDL_Renderer* sdlrenderer)
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

void SSW_GraphicsElement_TTF::setBodyText (std::string bodyText)
{
	bodyText_ = bodyText;
	textureNeedsUpdate_ = true;
}

void SSW_GraphicsElement_TTF::setTTFFont (TTF_Font* ttfFont)
{
	ttfFont_ = ttfFont;
	textureNeedsUpdate_ = true;
}

void SSW_GraphicsElement_TTF::setTextColor (SDL_Color textColor)
{
	textColor_ = textColor;
	textureNeedsUpdate_ = true;
}

void SSW_GraphicsElement_TTF::updateTexture (SDL_Renderer* sdlrenderer)
{
	SDL_Surface* textSurface = NULL;

	textSurface = TTF_RenderText_Blended_Wrapped (ttfFont_, bodyText_.c_str (), textColor_, destRect_.w);
	sdltexture_ = SDL_CreateTextureFromSurface (sdlrenderer, textSurface);
	destRect_.w = textSurface->w;
	destRect_.h = textSurface->h;

	textureNeedsUpdate_ = false;

	SDL_FreeSurface (textSurface);
}
