#include <vector>
#include <algorithm>
#include <numeric>
#include <unordered_map>
#include <chrono>
#include <cstdio>
#include <cmath>
#include <cassert>

class PrimeSieve {
public:
  PrimeSieve() = default;

  PrimeSieve(size_t size)
      : size((assert(size > 0), size)),
        bitarray((size + 1) / 2, true)
  {}

  auto run_sieve() -> void {
    size_t factor = 3;
    size_t maxval = (size_t) std::sqrt(size);

    while (factor <= maxval) {
      // Find the next `true` value starting at `factor / 2`, and convert
      // it back to its corresponding integer
      factor = 2 * std::distance(bitarray.begin(),
                                 std::find(std::next(bitarray.begin(), factor / 2), bitarray.end(), true)
                                 ) + 1;

      for (size_t i = factor * factor; i < size; i += factor * 2) {
        clear_bit(i);
      }

      factor += 2;
    }
  }

  auto print_results(size_t passes, double duration, bool show_primes = false) const -> void {
    if (show_primes) {
      printf("2");
      for (size_t i = 1; i < bitarray.size(); i++) {
        if (bitarray[i]) {
          printf(", %zu", 2 * i + 1);
        }
      }
      printf("\n");
    }

    printf("Passes: %zu, Time: %.6f, Avg: %.9f, Limit: %zu, Count: %zu, Valid: %s\n",
        passes, duration, duration / (double) passes, size, count_primes(),
        validate_results() ? "true" : "false");

    printf("\n");
    printf("pro7onmatrix;%zu;%f;1;algorithm=base,faithful=yes,bits=1\n", passes, duration);
  }

public:
  static const std::unordered_map<size_t, size_t> prime_counts;

private:
  auto get_bit(size_t index) const -> bool {
    return index % 2 == 1 && bitarray[index / 2];
  }

  auto clear_bit(size_t index) -> void {
    assert(index % 2 == 1);
    bitarray[index / 2] = false;
  }

  auto count_primes() const -> size_t {
    // Return the count simply as a sum of all `true` values
    return std::accumulate(bitarray.begin(), bitarray.end(), 0);
  }

  auto validate_results() const -> bool {
    auto target = prime_counts.find(size);
    return target != prime_counts.end() && target->second == count_primes();
  }

private:
  size_t size;
  std::vector<bool> bitarray;
};

const std::unordered_map<size_t, size_t> PrimeSieve::prime_counts = {
  {10, 4},
  {100, 25},
  {1000, 168},
  {10000, 1229},
  {100000, 9592},
  {1000000, 78498},
  {10000000, 664579},
  {100000000, 5761455},
};

int main() {
  using namespace std::chrono;

  PrimeSieve sieve;
  size_t passes = 0;

  auto t0 = high_resolution_clock::now();

  while (duration_cast<seconds>(high_resolution_clock::now() - t0).count() < 5) {
    sieve = PrimeSieve(1000000);
    sieve.run_sieve();
    passes++;
  }

  double duration = duration_cast<nanoseconds>(high_resolution_clock::now() - t0).count() * 1e-9;
  sieve.print_results(passes, duration);

  return 0;
}

