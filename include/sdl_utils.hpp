#pragma once

#include "constant.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <cmath>
#include <sycl/sycl.hpp>

void initializeSDL(SDL_Window *&window, SDL_Renderer *&renderer,
                   SDL_Surface *&surface);

void clearScreen(SDL_Renderer *renderer);

void cleanup(sycl::queue &q, SDL_Renderer *renderer, SDL_Window *window,
             SDL_Surface *surface);

void saveRendererToImage(SDL_Surface *surface, SDL_Renderer *renderer,
                         const std::string &filename);