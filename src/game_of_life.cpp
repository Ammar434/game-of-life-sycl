#include "game_of_life.hpp"

type_t sigma(type_t x, type_t a, type_t alpha) {
  return 1.0f / (1.0f + expf(-(x - a) * 4 / alpha));
}

type_t sigma_n(type_t x, type_t a, type_t b) {
  return sigma(x, a, alpha_n) * (1 - sigma(x, b, alpha_n));
}

type_t sigma_m(type_t x, type_t y, type_t m) {

  return x * (1 - sigma(m, 0.5f, alpha_m)) + y * sigma(m, 0.5f, alpha_m);
}

SYCL_EXTERNAL type_t s(type_t n, type_t m) {
  return sigma_n(n, sigma_m(b1, d1, m), sigma_m(b2, d2, m));
}

SYCL_EXTERNAL int emod(int a, int b) { return (a % b + b) % b; }

sycl::queue init_sycl() {

  try {
    sycl::queue q = sycl::queue(sycl::cpu_selector_v);
    std::cout << "Running on device: "
              << q.get_device().get_info<sycl::info::device::name>()
              << std::endl;
    return q;
  } catch (...) {
    std::cout << "Failed to select CPU device. Exiting.\n";
    // return 1;
  }
  return sycl::queue(sycl::default_selector_v);
}

void init_array(std::vector<type_t> *display, sycl::queue q) {

  std::vector<int> seeds(begining_array * 2, 0);
  std::random_device rd;
  std::generate(seeds.begin(), seeds.end(), std::ref(rd));

  sycl::buffer<type_t, 1> buf(display->data(),
                              sycl::range<1>(m_height * m_width));
  sycl::buffer<int, 1> seed_buf(seeds.data(),
                                sycl::range<1>(begining_array * 2));

  try {
    q.submit([&](sycl::handler &h) {
      auto acc = buf.get_access<sycl::access::mode::write>(h);
      auto seed_acc = seed_buf.get_access<sycl::access::mode::read>(h);

      h.parallel_for(sycl::range<1>(begining_array), [=](sycl::id<1> id) {
        int index = id[0];

        oneapi::dpl::minstd_rand engine_x(seed_acc[index * 2]);
        oneapi::dpl::minstd_rand engine_y(seed_acc[index * 2 + 1]);
        oneapi::dpl::uniform_int_distribution<int> distr_x(0, m_width - ra - 1);
        oneapi::dpl::uniform_int_distribution<int> distr_y(0,
                                                           m_height - ra - 1);

        int c = distr_x(engine_x);
        int r = distr_y(engine_y);

        for (int dr = 0; dr < ra && r + dr < m_height; ++dr) {
          for (int dc = 0; dc < ra && c + dc < m_width; ++dc) {
            acc[(r + dr) * m_height + (c + dc)] = 1.0f;
          }
        }
      });
    });
    q.wait_and_throw();
    std::cout << "SYCL array initialized successfully" << std::endl;
  } catch (sycl::exception const &e) {
    std::cout << "SYCL exception caught: " << e.what() << std::endl;
  }
}

void compute_grid_diff_sycl(sycl::buffer<type_t, 1> display_buf,
                            sycl::queue q) {

  q.submit([&](sycl::handler &h) {
    auto display_acc =
        display_buf.get_access<sycl::access::mode::read_write>(h);

    h.parallel_for(sycl::range<2>(m_height, m_width), [=](sycl::id<2> idx) {
      int x = idx[1];
      int y = idx[0];
      type_t m = 0, M = 0;
      type_t n = 0, N = 0;
      for (int dy = -(ra - 1); dy <= (ra - 1); dy++) {
        for (int dx = -(ra - 1); dx <= (ra - 1); dx++) {

          type_t dist_sq = dx * dx + dy * dy;
          if (dist_sq > ra_sq)
            continue;

          int nx = emod(x + dx, m_width);
          int ny = emod(y + dy, m_height);
          if (dist_sq <= ri_sq) {
            m += display_acc[ny * m_height + nx];
            M += 1;
          } else if (dist_sq <= ra_sq) {
            n += display_acc[ny * m_height + nx];
            N += 1;
          }
        }
      }

      m = (M > 0) ? m / M : type_t(0);
      n = (N > 0) ? n / N : type_t(0);

      type_t q = s(n, m);
      type_t diff = 2 * q - 1;

      int index = y * m_height + x;

      display_acc[index] =
          sycl::fmin(sycl::fmax(display_acc[index] + diff * dt, 0.0f), 1.0f);
    });
  });
}

void render_grid(sycl::buffer<type_t, 1> display_buf, SDL_Renderer *renderer) {
  sycl::host_accessor display(display_buf, sycl::read_only);

  for (int y = 0; y < m_height; y++) {
    for (int x = 0; x < m_width; x++) {
      type_t cellValue = display[y * m_height + x];
      // Alive cells: Vibrant green
      if (cellValue > 0.9f) {
        SDL_SetRenderDrawColor(renderer, 0, 255, 127, 255);
      }
      // Dead cells: Dark gray
      else if (cellValue < 0.1f) {
        SDL_SetRenderDrawColor(renderer, 40, 40, 40, 255);
      }
      // Transitioning cells: Gradient from blue to purple
      else {
        int blue = (255 * (1.0f - cellValue));
        int red = (255 * cellValue);
        SDL_SetRenderDrawColor(renderer, red, 0, blue, 255);
      }

      SDL_RenderDrawPoint(renderer, x, y);
    }
  }
}
