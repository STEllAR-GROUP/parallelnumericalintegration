//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <hpx/execution.hpp>
#include <hpx/execution/algorithms/sync_wait.hpp>
#include <hpx/execution_base/sender.hpp>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <kernel.hpp>
#include <pbm.hpp>

typedef std::complex<double> complex;

using namespace hpx::execution::experimental;

template <typename T>
concept sender = is_sender_v<T>;

namespace tt = hpx::this_thread::experimental;

void run(size_t pixel_x, size_t pixel_y, PBM* pbm) {
  thread_pool_scheduler sch{};

  // size_t partition_size = pixel_x / hpx::get_os_thread_count();
  // std::vector<double> partial_results(partition_size);

  sender auto s =
      schedule(sch) | bulk(pixel_x, [pixel_x, pixel_y, &pbm](auto i) {
        complex c =
            complex(0, 4) * complex(i, 0) / complex(pixel_x, 0) - complex(0, 2);

        for (size_t j = 0; j < pixel_y; j++) {
          int value = compute_pixel(c + 4.0 * j / pixel_y - 2.0);
          std::tuple<size_t, size_t, size_t> color = get_rgb(value);
          pbm->row(i)[j] = make_color(std::get<0>(color), std::get<1>(color),
                                      std::get<2>(color));
        }
      });

  *tt::sync_wait(std::move(s));
}

int main(int args, char** argv) {
  int pixel_x = std::stoi(argv[1]);
  int pixel_y = std::stoi(argv[2]);

  PBM pbm(pixel_x, pixel_y);

  auto start = std::chrono::high_resolution_clock::now();

  run(pixel_x, pixel_y, &pbm);

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << pixel_x * pixel_y << "," << diff.count() << std::endl;

  pbm.save("image_sender_receiver.pbm");

  return EXIT_SUCCESS;
}
