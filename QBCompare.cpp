// https://quick-bench.com/q/-9eUsE9JF_nbp1EepUABDffgpQU
/*
    A benchmark of short string comparisions. Compares the entire string.

    Result is true, as this requires all the text to be compared.
    Change the variable VALUE to test different options

    * Code before the loop is not measured
    * Code inside the loop is measured repeatedly
    * `benchmark::DoNotOptimize()` makes sure the variable is not optimized away by compiler

    The basic scenarios include the string matching exactly, i.e., `result` is true.
    As for mismatches:

    * The strings have a different length
    * The strings differ on the first character
    * The strings differ on the last character only
 */

#include <string>
#include <string_view>
#include <cstring>

using namespace ::std::literals::string_view_literals;

const char* VALUE = 
//                    "abcd"; // match up to last
//                    "def";  // differ on first character
                    "abd";  // differ on last character

static void StdString_With_CStringLiteral(benchmark::State& state) {
    std::string s(VALUE);
    for (auto _ : state) {

        bool result = s == "abc";

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdString_With_CStringLiteral);

static void strcmp(benchmark::State& state) {
    std::string s(VALUE);
    for (auto _ : state) {

        bool result = strcmp(s.data(), "abc") == 0;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(strcmp);

/*
static void Characters(benchmark::State& state) {
    std::string s(VALUE);
    for (auto _ : state) {

        bool result = s.size() == 3 &&
                      s[0] == 'a' &&
                      s[1] == 'b' &&
                      s[2] == 'c';

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Characters);
*/

static void Characters_Match(benchmark::State& state) {
    std::string s("abc");
    for (auto _ : state) {

        bool result = s.size() == 3 &&
                      s[0] == 'a' &&
                      s[1] == 'b' &&
                      s[2] == 'c';

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Characters_Match);

static void Characters_Mismatch_Length(benchmark::State& state) {
    std::string s("abcd");
    for (auto _ : state) {

        bool result = s.size() == 3 &&
                      s[0] == 'a' &&
                      s[1] == 'b' &&
                      s[2] == 'c';

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Characters_Mismatch_Length);

static void Characters_Mismatch_First_Character(benchmark::State& state) {
    std::string s("def");
    for (auto _ : state) {

        bool result = s.size() == 3 &&
                      s[0] == 'a' &&
                      s[1] == 'b' &&
                      s[2] == 'c';

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Characters_Mismatch_First_Character);

static void Characters_Mismatch_Last_Character(benchmark::State& state) {
    std::string s("abd");
    for (auto _ : state) {

        bool result = s.size() == 3 &&
                      s[0] == 'a' &&
                      s[1] == 'b' &&
                      s[2] == 'c';

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(Characters_Mismatch_Last_Character);

static void StdString_With_StdStringViewLiteral_Match(benchmark::State& state) {
    std::string s("abc");
    for (auto _ : state) {

        bool result = s == "abc"sv;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdString_With_StdStringViewLiteral_Match);


static void StdString_With_StdStringViewLiteral_Mismatch_Length(benchmark::State& state) {
    std::string s("abde");
    for (auto _ : state) {

        bool result = s == "abc"sv;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdString_With_StdStringViewLiteral_Mismatch_Length);

static void StdString_With_StdStringViewLiteral_Mismatch_First_Character(benchmark::State& state) {
    std::string s("def");
    for (auto _ : state) {

        bool result = s == "abc"sv;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdString_With_StdStringViewLiteral_Mismatch_First_Character);

static void StdString_With_StdStringViewLiteral_Mismatch_Last_Character(benchmark::State& state) {
    std::string s("abd");
    for (auto _ : state) {

        bool result = s == "abc"sv;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdString_With_StdStringViewLiteral_Mismatch_Last_Character);

static void StdStringViewCompare_With_CStringLiteral(benchmark::State& state) {
    std::string_view s(VALUE);
    for (auto _ : state) {

        bool result = s.compare("abc") == 0;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdStringViewCompare_With_CStringLiteral);

static void StdStringViewCompare_With_StdStringViewLiteral(benchmark::State& state) {
    std::string_view s(VALUE);
    for (auto _ : state) {

        bool result = s.compare("abc"sv) == 0;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdStringViewCompare_With_StdStringViewLiteral);

static void StdStringViewLiteral_With_StdStringView(benchmark::State& state) {
    std::string_view s(VALUE);
    for (auto _ : state) {

        bool result = "abc"sv.compare(s) == 0;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(StdStringViewLiteral_With_StdStringView);

#include <vector>
#include <string>
#include <algorithm>
#include <string_view>

using namespace std::literals::string_literals;
using namespace ::std::literals::string_view_literals;

static std::string s = "jlakjdlkajdskljdsfaladsfjkdasfkasdjsafkdjdfsakl>";

const char* p = "abc";


static void SandP(benchmark::State& state) {
    std::string_view s(VALUE);
    for (auto _ : state) {

        bool result = s == p;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(SandP);

static void SandSV(benchmark::State& state) {
    std::string_view s(VALUE);
    for (auto _ : state) {

        std::string_view sv(p);

        bool result = s == sv;

        benchmark::DoNotOptimize(result);
    }
}
BENCHMARK(SandSV);
