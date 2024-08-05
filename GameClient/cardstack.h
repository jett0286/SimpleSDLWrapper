#pragma once

#include <stack>

#include "playingcard.h"

class CardStack
{
	public:
		CardStack ();

		void pushCard (PlayingCard*);
		PlayingCard* popCard ();

		void setDestRect (SDL_Rect destRect);

		void registerElements (SSW_Window*);
		
	private:
		std::stack<PlayingCard*> stackCardsInPile_;

		SSW_GraphicsElement_SolidColor gfxElemBackground; 
		SDL_Rect destRect_;
};