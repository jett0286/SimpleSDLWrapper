#include "playingcard.h"

PlayingCard::PlayingCard ()
{
	destRect_ = {0, 0, 100, 100};
	updateElemRects ();
	denomination_ = NO_DENOM;
	suit_ = NO_SUIT;
}

PlayingCard::PlayingCard (SSW_Sprite* pSprite, PlayingCard_Denomination denomination, PlayingCard_Suit suit)
{
	gfxElement_.setSprite (pSprite);
	destRect_ = { 0, 0, 100, 100 };
	updateElemRects ();
	denomination_ = denomination;
	suit_ = suit;
}

void PlayingCard::setDestRect (SDL_Rect destRect)
{
	destRect_ = destRect;
	updateElemRects ();
}

void PlayingCard::setSprite (SSW_Sprite* pSprite)
{
	gfxElement_.setSprite (pSprite);
}

void PlayingCard::registerElems (SSW_Window* pWindow)
{
	pWindow->registerGraphicsElement (&gfxElement_);
}

void PlayingCard::updateElemRects ()
{
	gfxElement_.setDestRect (destRect_);
}
