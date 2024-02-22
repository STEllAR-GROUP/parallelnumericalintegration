//  Copyright (c) 2023 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <hpx/future.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>
#include <kernel.hpp>
#include <pbm.hpp>
#include <vector>

typedef std::complex<double> complex;

void launch(size_t i, size_t pixel_x, size_t pixel_y, PBM* pbm) {
  complex c =
      complex(0, 4) * complex(i, 0) / complex(pixel_x, 0) - complex(0, 2);

  for (size_t j = 0; j < pixel_y; j++) {
    int value = compute_pixel(c + 4.0 * j / pixel_y - 2.0);
    // std::cout << value << std::endl;
    std::tuple<size_t, size_t, size_t> color = get_rgb(value);
    // std::cout << std::get<0>(color) << " "  <<std::get<1>(color) << " " <<
    // std::get<2>(color) << std::endl;
    pbm->row(i)[j] =
        make_color(std::get<0>(color), std::get<1>(color), std::get<2>(color));
  }
}

int main(int args, char** argv) {
  int pixel_x = std::stoi(argv[1]);
  int pixel_y = std::stoi(argv[2]);

  PBM pbm(pixel_x, pixel_y);

  auto start = std::chrono::high_resolution_clock::now();

  std::vector<hpx::future<void>> futures;

  for (size_t i = 0; i < pixel_x; i++) {
    futures.push_back(std::move(hpx::async(launch, i, pixel_x, pixel_y, &pbm)));
  }

  hpx::when_all(futures).get();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << pixel_x * pixel_y << "," << diff.count() << std::endl;

  pbm.save("image_future.pbm");

  return EXIT_SUCCESS;
}
