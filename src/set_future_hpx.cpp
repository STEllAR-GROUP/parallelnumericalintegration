//  Copyright (c) 2023 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <hpx/hpx_main.hpp>
#include <hpx/future.hpp>
#include <kernel.hpp>
#include <pbm.hpp>

typedef std::complex<double> complex;

int main(int args, char** argv) {
  int pixel_x = std::stoi(argv[1]);
  int pixel_y = std::stoi(argv[2]);
  
  auto start = std::chrono::high_resolution_clock::now();

  std::vector<hpx::future<std::vector<int>>> futures;
  
  for (size_t i = 0; i < pixel_x ; i++ )
  {
   

    futures.push_back(std::move(hpx::async([&](){

    std::vector<int> row;
    complex c = 
        complex(0, 4) * complex(i, 0) / complex(pixel_x, 0) - complex(0, 2);

      for(size_t j = 0 ; j < pixel_y ; j++){

        int value = compute_pixel(c + 4.0 * j / pixel_y - 2.0);
        std::tuple<size_t, size_t, size_t> color = get_rgb(value);
        row.push_back(make_color(std::get<0>(color), std::get<1>(color),
                                std::get<2>(color)));

    }
    return row;

    })));
  }

  hpx::when_all(futures).then([pixel_x,pixel_y](auto&& f){

    auto futures = f.get();
    PBM pbm(pixel_x,pixel_y);

    for(size_t i = 0 ; i < pixel_x ; i++)
        pbm.row(i) = futures[i].get();

    
    pbm.save("image_future.pbm");

  }).get();

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << pixel_x * pixel_y << "," << diff.count() << std::endl;
  return EXIT_SUCCESS;
}
