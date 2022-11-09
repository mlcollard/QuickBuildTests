// https://quick-bench.com/q/I2tI_8q3WozGE5N7Z0oGG4sV_bo
#include <string_view>
#include <string>
#include <cstring>

using namespace ::std::literals::string_view_literals;

const char* s = "djlakjsdlkjfdajadfskljdfsl";

static void FindStrLen(benchmark::State& state) {
  for (auto _ : state) {

    int result = strlen(s);

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(FindStrLen);

static void FindStringView(benchmark::State& state) {
  for (auto _ : state) {

    int result = std::string_view(s).size();

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(FindStringView);
