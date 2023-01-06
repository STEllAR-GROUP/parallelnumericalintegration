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

int main() {
  double x = .1;
  double r = run(10000, 10, x);
  double a = log(1 + x);
  std::cout << "r=" << r << " ~ " << a << " => " << fabs(r - a) << std::endl;
}
