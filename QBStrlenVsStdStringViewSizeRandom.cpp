// https://quick-bench.com/q/PwOWbtQAP58m1837d6vU8us-mAs
#include <string>
#include <string_view>
#include <algorithm>
#include <cstring>
#include <cstdlib>

// generate a randome string of size length
// set srand() for common sequences
std::string random_string(int length) {

    auto randchar = []() -> char {
        const char charset[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        const size_t max_index = sizeof(charset) - 1;
        return charset[rand() % max_index];
    };

    std::string str(length, 0);
    std::generate_n(str.begin(), length, randchar);

    return str;
}

static void StrLen(benchmark::State& state) {
  srand(1);
  for (auto _ : state) {

    auto p = random_string(10).data();
    auto result = strlen(p);

    benchmark::DoNotOptimize(result);
  }
}
// Register the function as a benchmark
BENCHMARK(StrLen)->Name("strlen(p)");

static void StdStringViewSize(benchmark::State& state) {
  srand(1);
  for (auto _ : state) {

    auto p = random_string(10).data();
    auto result = std::string_view(p).size();

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StdStringViewSize)->Name("std::string_view(p).size()");
