// https://quick-bench.com/q/-zjhvd82zYFFro1zPurlJivQ0E8
static void StringCreation(benchmark::State& state) {

  std::vector<int> vec(1000, 0);
  for (auto _ : state) {

    int total = 0;
    for (std::size_t i = 0; i < vec.size(); i++) {
        total += vec[i];
    }

    benchmark::DoNotOptimize(total);
  }
}
// Register the function as a benchmark
BENCHMARK(StringCreation);

static void StringCopy(benchmark::State& state) {
  std::vector<int> vec(1000, 0);
  for (auto _ : state) {

    int total = 0;
    for (const auto n : vec) {
        total += n;
    }

    benchmark::DoNotOptimize(total);
  }
}
BENCHMARK(StringCopy);
