
#include "graphicsmanager.h"

SSW_GraphicsManager::~SSW_GraphicsManager ()
{
  SDL_DestroyWindow (sdlwindow_);
  SDL_DestroyRenderer (sdlrenderer_);
  SDL_DestroyTexture (spritesheet_);

  for (SSW_Sprite* pSprite : vectorSpriteData_)
  {
    delete pSprite;
  }
  vectorSpriteData_.clear ();
  mSpritesTable_.clear ();
  
  for (SSW_GraphicsElement* pGraphicsElement : vectorGraphicsElements_)
  {
    delete pGraphicsElement;
  }
  vectorGraphicsElements_.clear ();
}

bool SSW_GraphicsManager::init (int winHeight, int winWidth)
{
  sdlrenderer_ = NULL;
  sdlwindow_ = NULL;
  spritesheet_ = NULL;
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

  for (int i = (int)vectorGraphicsElements_.size() - 1; i >= 0; i--)
  {
    vectorGraphicsElements_[i]->render (sdlrenderer_);
  }

  SDL_SetRenderDrawColor (sdlrenderer_, backgroundColor_.r, backgroundColor_.g, backgroundColor_.b, backgroundColor_.a);
  SDL_RenderPresent (sdlrenderer_); 
}

void SSW_GraphicsManager::setBackgroundColor (SDL_Color backgroundColor)
{
  backgroundColor_ = backgroundColor;
}

void SSW_GraphicsManager::registerGraphicsElement (SSW_GraphicsElement* graphicsElement)
{
  vectorGraphicsElements_.push_back (graphicsElement);
}

void SSW_GraphicsManager::registerGraphicsElementFront (SSW_GraphicsElement* graphicsElement)
{
  vectorGraphicsElements_.insert(vectorGraphicsElements_.begin (), graphicsElement);
}

void SSW_GraphicsManager::loadSprites (const char* spritesheetPath, int spriteHeight, int spriteWidth)
{
  SSW_Sprite* pActiveSprite;
  int spritesheetHeight;
  int spritesheetWidth;
  int numSpritesVert;
  int numSpritesHoriz;

  spritesheet_ = IMG_LoadTexture (sdlrenderer_, spritesheetPath);

  SDL_QueryTexture (spritesheet_, NULL, NULL, &spritesheetWidth, &spritesheetHeight);
  numSpritesVert = spritesheetHeight / spriteHeight;
  numSpritesHoriz = spritesheetWidth / spriteWidth;

  for (int y = 0; y < numSpritesVert; y++)
  {
    for (int x = 0; x < numSpritesHoriz; x++)
    {
      pActiveSprite = new SSW_Sprite (spritesheet_, x * spriteWidth, y * spriteHeight, spriteWidth, spriteHeight);
      vectorSpriteData_.push_back (pActiveSprite);
    }
  }
}

void SSW_GraphicsManager::unloadSprites ()
{
  spritesheet_ = NULL;
  for (SSW_Sprite* pSprite : vectorSpriteData_)
  {
    delete pSprite;
  }
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