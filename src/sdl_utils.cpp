#include "sdl_utils.hpp"
#include <iomanip>
#include <sstream>

void initializeSDL(SDL_Window *&window, SDL_Renderer *&renderer,
                   SDL_Surface *&surface) {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    throw std::runtime_error("SDL could not initialize! SDL_Error: " +
                             std::string(SDL_GetError()));
  }

  // Create window
  window = SDL_CreateWindow("Game of Life", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, m_width, m_height,
                            SDL_WINDOW_OPENGL);
  if (window == nullptr) {
    SDL_Quit();
    throw std::runtime_error("Window could not be created! SDL_Error: " +
                             std::string(SDL_GetError()));
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == nullptr) {
    SDL_DestroyWindow(window);
    SDL_Quit();
    throw std::runtime_error("Renderer could not be created! SDL_Error: " +
                             std::string(SDL_GetError()));
  }

  // Create surface
  surface = SDL_CreateRGBSurfaceWithFormat(0, m_width, m_height, 32,
                                           SDL_PIXELFORMAT_ARGB8888);
  if (surface == nullptr) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    throw std::runtime_error("SDL_CreateRGBSurface Error: " +
                             std::string(SDL_GetError()));
  }
}

void cleanup(sycl::queue &q, SDL_Renderer *renderer, SDL_Window *window,
             SDL_Surface *surface) {

  SDL_DestroyRenderer(renderer);
  SDL_FreeSurface(surface);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

// Function to save SDL renderer content as a JPEG file
void saveRendererToImage(SDL_Surface *surface, SDL_Renderer *renderer,
                         const std::string &filename) {

  // Read pixels from the renderer into the surface
  if (SDL_RenderReadPixels(renderer, NULL, SDL_PIXELFORMAT_ARGB8888,
                           surface->pixels, surface->pitch) != 0) {
    std::cerr << "SDL_RenderReadPixels Error: " << SDL_GetError() << std::endl;
    return;
  }

  // Save the surface as a JPEG file
  if (IMG_SaveJPG(surface, filename.c_str(), 70) != 0) {
    std::cerr << "IMG_SaveJPG Error: " << IMG_GetError() << std::endl;
  }
}

void clearScreen(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}