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

using namespace hpx::execution::experimental;

template <typename T>
concept sender = is_sender_v<T>;

namespace tt = hpx::this_thread::experimental;

double run(size_t n, size_t num_threads, double x) {
  thread_pool_scheduler sch{};

  size_t partition_size = n / num_threads;
  std::vector<double> partial_results(partition_size);

  sender auto s = schedule(sch) |
                  bulk(num_threads,
                       [&](auto i) {
                         size_t begin = i * partition_size;
                         size_t end = (i + 1) * partition_size;
                         if (i == num_threads - 1) end = n;
                         double partial_sum = 0;
                         for (int i = begin; i <= end; i++) {
                           double e = i + 1;
                           double term =
                               std::pow(-1.0, e + 1) * std::pow(x, e) / e;
                           partial_sum += term;
                         }
                         partial_results[i] = partial_sum;
                       }) |
                  then([&]() {
                    double sum = 0;
                    for (int i = 0; i < partition_size; i++)
                      sum += partial_results[i];
                    return sum;
                  });
  auto result = hpx::get<0>(*tt::sync_wait(std::move(s)));
  return result;
}

int main(int args, char** argv) {
  size_t threads = std::stoi(argv[3]);
  double x = std::stod(argv[2]);
  size_t n = std::stoi(argv[1]);

  auto start = std::chrono::high_resolution_clock::now();
  double result = run(n, threads, x);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> diff = end - start;
  std::cout << threads << "," << diff.count() << std::endl;

  std::cout << "Difference of Taylor and C++ result " << result - std::log1p(x)
            << " after " << n << " iterations." << std::endl;
  return EXIT_SUCCESS;
}
