#include "simplesdl.h"

SSW_Window::SSW_Window ()
{
  graphicsMan_.initSDL (480, 640);
}

SSW_Window::SSW_Window (int winHeight, int winWidth)
{
  graphicsMan_.initSDL (winHeight, winWidth);
}

void SSW_Window::refresh ()
{
  graphicsMan_.refresh ();
}

void SSW_Window::setBackgroundColor (SDL_Color backgroundColor)
{
  graphicsMan_.setBackgroundColor (backgroundColor);
}

void SSW_Window::loadSprites (const char* spritesheetPath, int spriteHeight, int spriteWidth)
{
  graphicsMan_.loadSprites (spritesheetPath, spriteHeight, spriteWidth);
}

void SSW_Window::unloadSprites ()
{
  graphicsMan_.unloadSprites ();
}

SSW_Sprite* SSW_Window::getSpriteFromID (int spriteID)
{
  return graphicsMan_.getSpriteFromID (spriteID);
}

void SSW_Window::mapKey (SDL_Keycode kcode, SSW_Command_Base* pCommand)
{
  inputMan_.encodeMapKey (kcode, pCommand);
}

void SSW_Window::unmapKey (SDL_Keycode kcode)
{
  inputMan_.unmapKey (kcode);
}

void SSW_Window::remapKey (SDL_Keycode src, SDL_Keycode dest)
{
  inputMan_.remapKey (src, dest);
}

void SSW_Window::handleInput ()
{
  inputMan_.awaitInput ();
}

void SSW_Window::registerGraphicsElement (SSW_GraphicsElement_Base* graphicsElement)
{
  graphicsMan_.registerGraphicsElement (graphicsElement);
}

void SSW_Window::registerMouseElement (SSW_MouseElement* mouseElement)
{
  inputMan_.registerMouseElement (mouseElement);
}