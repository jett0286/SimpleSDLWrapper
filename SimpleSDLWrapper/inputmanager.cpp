#include "inputmanager.h"

SSW_InputManager::SSW_InputManager ()
{
  ctrlHeld_ = false;
  shiftHeld_ = false;
  altHeld_ = false;
  currentEvent_ = {0}; // gets rid of a visual studio warning
}

void SSW_InputManager::encodeMapKey (SDL_Keycode kcode, SSW_Command_Base* pCommand)
{
	keyPressMap_.emplace(kcode, pCommand);
}

void SSW_InputManager::unmapKey (SDL_Keycode kcode)
{
  delete keyPressMap_[kcode];
}

void SSW_InputManager::remapKey (SDL_Keycode kcodeSrc, SDL_Keycode kcodeDest)
{
  keyPressMap_[kcodeDest] = keyPressMap_[kcodeSrc];
  keyPressMap_[kcodeSrc] = NULL;
}

void SSW_InputManager::registerMouseElement (SSW_MouseElement* mouseElement)
{
  std::vector<SSW_MouseElement*>::iterator i;
  
  for (i = vectorMouseElements_.begin (); i != vectorMouseElements_.end (); i++)
  {
    // IF SOMETHING DOESN"T WORK WITH PRIORITY< IT"S PROBABLY THIS
    if (mouseElement->getPriority() > (*i)->getPriority ())
    {
      continue;
    }
    else if (mouseElement->getPriority() == (*i)->getPriority())
    {
      break;
    }
    else
    {
      i--; // overstep of 1, stepping back
      break;
    }
  }
  vectorMouseElements_.insert (i, mouseElement);
}

SSW_Command_Base* SSW_InputManager::getCommandFromKey (SDL_Keycode kcode)
{
  return keyPressMap_[kcode];
}

void SSW_InputManager::awaitInput ()
{
  while (SDL_PollEvent (&currentEvent_))
  {
    executeInput (currentEvent_);
  }
}

void SSW_InputManager::executeInput (SDL_Event sdlevent)
{
  switch (sdlevent.type)
  {
    case SDL_QUIT:
      exit (EXIT_SUCCESS);
      break;
    case SDL_KEYDOWN:
      executeKeyPress (sdlevent.key.keysym.sym);
      break;
    case SDL_KEYUP:
      executeKeyUp (sdlevent.key.keysym.sym);
      break;
    case SDL_MOUSEBUTTONDOWN:
      executeMouseClick (sdlevent.button.button);
      break;
    case SDL_MOUSEBUTTONUP:
      executeMouseUnclick (sdlevent.button.button);
      break;
    case SDL_MOUSEMOTION:
      executeMouseMove ();
      break;
    case SDL_WINDOWEVENT:
      handleWindowEvent (sdlevent.window.event);
      break;
  }
}

void SSW_InputManager::executeKeyPress (SDL_Keycode kcode)
{
  switch (kcode)
  {
    case NULL:
      break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
      ctrlHeld_ = true;
      break;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
      shiftHeld_ = true;
      break;
    case SDLK_LALT:
    case SDLK_RALT:
      altHeld_ = true;
      break;
    default:
      if (keyPressMap_[kcode] != NULL)
      {
        keyPressMap_[kcode]->execute ();
      }
      else
      {
        break;
      }
  }
}

void SSW_InputManager::executeKeyUp (SDL_Keycode kcode)
{
  switch (kcode)
  {
    case NULL:
      break;
    case SDLK_LCTRL:
    case SDLK_RCTRL:
      ctrlHeld_ = false;
      break;
    case SDLK_LSHIFT:
    case SDLK_RSHIFT:
      shiftHeld_ = false;
      break;
    case SDLK_LALT:
    case SDLK_RALT:
      altHeld_ = false;
      break;
    default:
      break;
  }
}

void SSW_InputManager::executeMouseClick (Uint8 mouseButtonIndex)
{
  int mouseX;
  int mouseY;

  SDL_GetMouseState (&mouseX, &mouseY);
  switch (mouseButtonIndex)
  {
    case 1:
      for (SSW_MouseElement* mouseElement : vectorMouseElements_)
      {
        if (mouseElement->intersects (mouseX, mouseY))
        {
          mouseElement->executeLeftClick ();
          return;
        }
      }
    case 3:
      for (SSW_MouseElement* mouseElement : vectorMouseElements_)
      {
        if (mouseElement->intersects (mouseX, mouseY))
        {
          mouseElement->executeRightClick ();
          return;
        }
      }
  }
  
}

void SSW_InputManager::executeMouseUnclick (Uint8 mouseButtonIndex)
{
  switch (mouseButtonIndex)
  {
    case 1:
      for (SSW_MouseElement* inputElement : vectorMouseElements_)
      {
        inputElement->executeLeftUnclick ();
      }
    case 3:
      for (SSW_MouseElement* inputElement : vectorMouseElements_)
      {
        inputElement->executeRightUnclick ();
      }
  }
}

void SSW_InputManager::executeMouseMove ()
{
  for (SSW_MouseElement* inputElement : vectorMouseElements_)
  {
    inputElement->executeMouseMove ();
  }
}

void SSW_InputManager::handleWindowEvent (uint8_t windowEvent)
{
  int width = 0;
  int height = 0;
  switch (windowEvent)
  {
    case SDL_WINDOWEVENT_SIZE_CHANGED:
      //std::cout << "Window size changed\n";
      break;
    case SDL_WINDOWEVENT_MOVED:
      //std::cout << "Window moved\n";
      break;
    default:
      break;
  }
}
