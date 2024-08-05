
#include "graphicsmanager.h"

SSW_GraphicsManager::SSW_GraphicsManager ()
{
  winWidth_ = 640;
  winHeight_ = 480;
  sdlwindow_ = NULL;
  sdlrenderer_ = NULL;
  backgroundColor_ = {0x00, 0x00, 0x00, 0xFF};
}

SSW_GraphicsManager::~SSW_GraphicsManager ()
{
  SDL_DestroyWindow (sdlwindow_);
  SDL_DestroyRenderer (sdlrenderer_);
  
  unloadSprites ();
  
  for (SSW_GraphicsElement_Base* pGraphicsElement : vectorGraphicsElements_)
  {
    delete pGraphicsElement;
  }
  vectorGraphicsElements_.clear ();
}

bool SSW_GraphicsManager::initSDL (int winHeight, int winWidth)
{
  sdlrenderer_ = NULL;
  sdlwindow_ = NULL;
  backgroundColor_ = {0x00, 0x00, 0x00, 0xFF};
  winHeight_ = winHeight;
  winWidth_ = winWidth;

  if (SDL_Init (SDL_INIT_VIDEO) < 0)
  {
    exit (EXIT_FAILURE);
  }
  if (!initSDLWindow (winWidth, winHeight))
  {
    exit (EXIT_FAILURE);
  }
  if (!initSDLRenderer ())
  {
    exit (EXIT_FAILURE);
  }
  if (!initSDLImage ())
  {
    exit (EXIT_FAILURE);
  }
  if (!initSDLTTF ())
  {
    exit (EXIT_FAILURE);
  }
  return true;
}

void SSW_GraphicsManager::refresh ()
{
  SDL_RenderClear (sdlrenderer_);

  for (SSW_GraphicsElement_Base* pGfxElement : vectorGraphicsElements_)
  {
    pGfxElement->render (sdlrenderer_);
  }

  SDL_SetRenderDrawColor (sdlrenderer_, backgroundColor_.r, backgroundColor_.g, backgroundColor_.b, backgroundColor_.a);
  SDL_RenderPresent (sdlrenderer_); 
}

void SSW_GraphicsManager::setBackgroundColor (SDL_Color backgroundColor)
{
  backgroundColor_ = backgroundColor;
}

void SSW_GraphicsManager::registerGraphicsElement (SSW_GraphicsElement_Base* graphicsElement)
{
  std::vector<SSW_GraphicsElement_Base*>::iterator i;

  for (i = vectorGraphicsElements_.begin (); i != vectorGraphicsElements_.end (); i++)
  {
    // IF SOMETHING DOESN'T WORK WITH PRIORITY, IT'S PROBABLY THIS
    // NOTE: VECTOR IS STORED IN INCREASING PRIORITY ORDER
    if (graphicsElement->getPriority () > (*i)->getPriority ())
    {
      continue;
    }
    else
    {
      break;
    }
  }
  vectorGraphicsElements_.insert (i, graphicsElement);
}

void SSW_GraphicsManager::loadSprites (const char* spritesheetPath, int spriteHeight, int spriteWidth, int maxSpritesToLoad)
{
  SSW_Sprite* pActiveSprite;
  SDL_Texture* spritesheet = IMG_LoadTexture (sdlrenderer_, spritesheetPath);
  int spritesheetHeight;
  int spritesheetWidth;
  int numSpritesVert;
  int numSpritesHoriz;
  int i = 0;

  vectorSpritesheets_.push_back (spritesheet);

  SDL_QueryTexture (spritesheet, NULL, NULL, &spritesheetWidth, &spritesheetHeight);
  numSpritesVert = spritesheetHeight / spriteHeight;
  numSpritesHoriz = spritesheetWidth / spriteWidth;

  for (int y = 0; y < numSpritesVert; y++)
  {
    for (int x = 0; x < numSpritesHoriz; x++)
    {
      i++;
      if (i > maxSpritesToLoad)
      {
        return;
      }
      pActiveSprite = new SSW_Sprite (spritesheet, x * spriteWidth, y * spriteHeight, spriteWidth, spriteHeight);
      vectorSpriteData_.push_back (pActiveSprite);
    }
  }
}

void SSW_GraphicsManager::unloadSprites ()
{
  for (SDL_Texture* sdltexture : vectorSpritesheets_)
  {
    SDL_DestroyTexture (sdltexture);
  }
  for (SSW_Sprite* pSprite : vectorSpriteData_)
  {
    delete pSprite;
  }

  vectorSpritesheets_.clear ();
  vectorSpriteData_.clear ();
}

SSW_Sprite* SSW_GraphicsManager::getSpriteFromID (int spriteID)
{
  return vectorSpriteData_[spriteID];;
}

bool SSW_GraphicsManager::initSDLWindow (int winWidth, int winHeight)
{
  sdlwindow_ = SDL_CreateWindow ("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, winWidth, winHeight, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (sdlwindow_)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool SSW_GraphicsManager::initSDLRenderer ()
{
  sdlrenderer_ = SDL_CreateRenderer (sdlwindow_, -1, SDL_RENDERER_ACCELERATED);
  if (sdlrenderer_)
  {
    SDL_SetRenderDrawColor (sdlrenderer_, 0, 0, 0, 0xFF);
    return true;
  }
  else
  {
    return false;
  }
}

bool SSW_GraphicsManager::initSDLImage ()
{
  int imgFlags = IMG_INIT_PNG;
  if (!(IMG_Init (imgFlags) & imgFlags))
  {
    return false;
  }
  else
  {
    return true;
  }
}

bool SSW_GraphicsManager::initSDLTTF ()
{
  if (TTF_Init() < 0)
  {
    return false;
  }
  else
  {
    return true;
  }
}