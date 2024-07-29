#pragma once
#include "constant.hpp"
#include <SDL2/SDL.h>
#include <math.h>
#include <oneapi/dpl/random>
#include <random>
#include <sycl/sycl.hpp>

sycl::queue init_sycl();

void init_array(std::vector<type_t> *display, sycl::queue q);

type_t sigma(type_t x, type_t a, type_t alpha);
type_t sigma(type_t x, type_t a, type_t alpha);
type_t sigma_m(type_t x, type_t y, type_t m);
SYCL_EXTERNAL type_t s(type_t n, type_t m);
SYCL_EXTERNAL int emod(int a, int b);

void compute_grid_diff_sycl(sycl::buffer<type_t, 1> display_buf, sycl::queue q);
void render_grid(sycl::buffer<type_t, 1> display_buf, SDL_Renderer *renderer);