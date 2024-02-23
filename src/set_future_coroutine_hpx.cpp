//  Copyright (c) 2024 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <cmath>
#include <cstdlib>
#include <hpx/hpx_main.hpp>
#include <hpx/numeric.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <iostream>
#include <kernel.hpp>
#include <numeric>
#include <pbm.hpp>
#include <string>
#include <vector>

#ifdef __GNUC__
#ifndef __APPLE__
#include <coroutine>
#endif
#endif

typedef std::complex<double> complex;

hpx::future<void> run(size_t pixel_x, size_t pixel_y, PBM* pbm) {
  std::vector<hpx::future<void>> futures;

  for (size_t i = 0; i < pixel_x; i++) {
    futures.push_back(std::move(hpx::async([i, pixel_x, pixel_y, &pbm]() {
      complex c =
          complex(0, 4) * complex(i, 0) / complex(pixel_x, 0) - complex(0, 2);

      for (size_t j = 0; j < pixel_y; j++) {
        int value = compute_pixel(c + 4.0 * j / pixel_y - 2.0);
        std::tuple<size_t, size_t, size_t> color = get_rgb(value);
        pbm->row(i)[j] = make_color(std::get<0>(color), std::get<1>(color),
                                    std::get<2>(color));
      }
    })));
  }

  auto futures2 = co_await hpx::when_all(futures);

  co_return;
}

int main(int args, char** argv) {
  int pixel_x = std::stoi(argv[1]);
  int pixel_y = std::stoi(argv[2]);

  PBM pbm(pixel_x, pixel_y);

  auto start = std::chrono::high_resolution_clock::now();

  run(pixel_x, pixel_y, &pbm).get();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << pixel_x * pixel_y << "," << diff.count() << std::endl;

  pbm.save("image_future_coroutine.pbm");

  return EXIT_SUCCESS;
}
