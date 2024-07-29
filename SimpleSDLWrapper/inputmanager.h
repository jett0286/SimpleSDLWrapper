#pragma once

#include <map>
#include <vector>

#include "mouseelement.h"

class SSW_InputManager
{
	public:
		SSW_InputManager ();

		void encodeMapKey (SDL_Keycode, SSW_Command*);
		void unmapKey (SDL_Keycode kcode);
		void remapKey (SDL_Keycode src, SDL_Keycode dest);
		
		void registerMouseElement (MouseElement* mouseElement);
		void registerMouseElementFront (MouseElement* mouseElement);

		SSW_Command* getCommandFromKey (SDL_Keycode kcode);
		// overloaded [] for getting and setting?

		void awaitInput ();
	private:
		void executeInput (SDL_Event);
		void executeKeyPress (SDL_Keycode);
		void executeKeyUp (SDL_Keycode);
		void executeMouseClick (Uint8 mouseButtonIndex);
		void executeMouseUnclick (Uint8 mouseButtonIndex);
		void executeMouseMove ();
		void handleWindowEvent (uint8_t windowEvent);

		SDL_Event currentEvent_;

		std::map<SDL_Keycode, SSW_Command*> keyPressMap_;

		std::vector<MouseElement*> vectorMouseElements_;

		bool ctrlHeld_;
		bool shiftHeld_;
		bool altHeld_;
};