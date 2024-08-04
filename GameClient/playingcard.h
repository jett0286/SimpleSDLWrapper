#pragma once

#include <simplesdl.h>

#define CARD_WIDTH 140
#define CARD_HEIGHT 190

enum PlayingCard_Denomination
{
	NO_DENOM = 0,
	ACE = 1,
	TWO = 2,
	THREE = 3,
	FOUR = 4,
	FIVE = 5,
	SIX = 6,
	SEVEN = 7,
	EIGHT = 8,
	NINE = 9,
	TEN = 10,
	JACK = 11,
	QUEEN = 12,
	KING = 13
};

enum PlayingCard_Suit
{
	NO_SUIT = 0,
	HEARTS = 1,
	SPADES = 2,
	DIAMONDS = 3,
	CLUBS = 4
};

class PlayingCard
{
	public:
		PlayingCard ();
		PlayingCard (SSW_Sprite*, PlayingCard_Denomination, PlayingCard_Suit);

		void setDestRect (SDL_Rect);
		void setSprite (SSW_Sprite*);

		void registerElems (SSW_Window*);
	private:
		SSW_GraphicsElement_Sprite gfxElement_;
		PlayingCard_Denomination denomination_;
		PlayingCard_Suit suit_;

		SDL_Rect destRect_;
		void updateElemRects ();
};