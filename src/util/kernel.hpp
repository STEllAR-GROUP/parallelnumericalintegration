//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <complex>

const size_t max_iterations = 80;
const double pi = M_PI;
const int max_color = 256;

size_t compute_pixel(std::complex<double> c) {
  // std::cout <<  " compute " << c << std::endl;
  std::complex<double> z(0, 0);

  for (size_t i = 0; i < max_iterations; i++) {
    z = z * z + c;
    // std::cout << "i " << i << std::endl;
    if (abs(z) > 2.0) {
      return (double)i + (2.0 - (log(abs(z)) / log(2.0)));
    }
  }
  return 0;
}

#endif
