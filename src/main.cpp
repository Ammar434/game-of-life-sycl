#include "constant.hpp"
#include "game_of_life.hpp"
#include "sdl_utils.hpp"
#include <iostream>

#include <chrono>
#include <sycl/sycl.hpp>
#include <time.h> /* time */
#include <vector>

int main() {
  srand(time(NULL));

  auto program_start = std::chrono::high_resolution_clock::now();

  bool running = true;
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Surface *surface;
  SDL_Event event;
  initializeSDL(window, renderer, surface);

  std::vector<type_t> display(m_height * m_width, 0.0f);

  sycl::queue q = init_sycl();

  init_array(&display, q);

  sycl::buffer<type_t, 1> display_buf(display.data(),
                                      sycl::range<1>(m_height * m_width));

  int frameCount = 0;
  double total_frame_time = 0.0;

  while (running) {
    auto frame_start = std::chrono::high_resolution_clock::now();

    clearScreen(renderer);

    compute_grid_diff_sycl(display_buf, q);
    q.wait_and_throw();

    // Render cells
    render_grid(display_buf, renderer);
    SDL_RenderPresent(renderer);
    saveRendererToImage(surface, renderer,
                        "images/screenshot_" + std::to_string(frameCount) +
                            ".jpg");

    auto frame_end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> frame_duration =
        frame_end - frame_start;

    total_frame_time += frame_duration.count();

    std::cout << "Frame " << frameCount
              << " generation time: " << frame_duration.count() << " ms"
              << std::endl;

    frameCount++;
  }

  auto program_end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> program_duration =
      program_end - program_start;

  std::cout << "\nTotal program execution time: " << program_duration.count()
            << " ms" << std::endl;
  std::cout << "Average frame generation time: "
            << total_frame_time / frameCount << " ms" << std::endl;

  cleanup(q, renderer, window, surface);
  return 0;
}