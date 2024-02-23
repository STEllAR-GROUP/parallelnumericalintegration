//  Copyright (c) 2023 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <hpx/hpx_main.hpp>
#include <hpx/parallel/algorithm.hpp>
#include <iostream>
#include <kernel.hpp>
#include <pbm.hpp>
#include <vector>

typedef std::complex<double> complex;

int main(int args, char** argv) {
  int pixel_x = std::stoi(argv[1]);
  int pixel_y = std::stoi(argv[2]);

  PBM pbm(pixel_x, pixel_y);

  auto start = std::chrono::high_resolution_clock::now();

  hpx::experimental::for_loop(
      hpx::execution::par, 0, pixel_x, [pixel_x, pixel_y, &pbm](size_t i) {
        complex c =
            complex(0, 4) * complex(i, 0) / complex(pixel_x, 0) - complex(0, 2);

        for (size_t j = 0; j < pixel_y; j++) {
          int value = compute_pixel(c + 4.0 * j / pixel_y - 2.0);
          std::tuple<size_t, size_t, size_t> color = get_rgb(value);
          pbm.row(i)[j] = make_color(std::get<0>(color), std::get<1>(color),
                                     std::get<2>(color));
        }
      });

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << pixel_x * pixel_y << "," << diff.count() << std::endl;

  //pbm.save("image_par.pbm");

  return EXIT_SUCCESS;
}
