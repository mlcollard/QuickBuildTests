// https://quick-bench.com/q/dFhn29sTLQVHV-wxTZ_cMHK3E9w
#include <string>
#include <string_view>
#include <algorithm>
#include <bitset>

const std::bitset<128> tagNameMask("00000111111111111111111111111110100001111111111111111111111111100000001111111111011000000000000000000000000000000000000000000000");

using namespace std::literals;

static std::string s = "                                             >";

constexpr auto WHITESPACE = " \n\t\r"sv;

#include <string.h>

static void StringCreation(benchmark::State& state) {
  for (auto _ : state) {

    auto result = std::none_of(s.cbegin(), s.cend(), [] (char c) { return c =='>'; });

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringCreation);

static void StringCopy(benchmark::State& state) {
  for (auto _ : state) {

    auto result = s.find('>') == s.npos;

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringCopy);

static void StringFind(benchmark::State& state) {
  for (auto _ : state) {

    auto result = s.cend() == std::find_if(s.cbegin(), s.cend(), [] (char c) { return c == '>'; });

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringFind);

static void StringFindLoop(benchmark::State& state) {
  for (auto _ : state) {

    auto result = s.find_first_not_of(WHITESPACE) != s.npos;

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringFindLoop);

static void StringFindLoop2(benchmark::State& state) {
  for (auto _ : state) {

    auto result = s.find_first_not_of(' ') == s.npos;

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringFindLoop2);

static void StringStrchr(benchmark::State& state) {
  for (auto _ : state) {

    auto result = strchr(s.data(), '>') == nullptr;

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringStrchr);

static void StringStrpbrk(benchmark::State& state) {
  for (auto _ : state) {

    auto result = strspn(s.data(), WHITESPACE.data()) == 0;

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringStrpbrk);

static void StringStrpbrkEncode(benchmark::State& state) {
  std::string_view str(s);
  for (auto _ : state) {

    // output any '<', '>', or '&', or any text before
    auto p = &str.data()[0];
    auto lastp = p;
    std::string result;
    for (p = strpbrk(p, "<>&"); p != 0 && *p != 0; p = strpbrk(p, "<>&")) {

        // output section before
        result += std::string_view(lastp, p - lastp);

        // output special characters
        if (*p == '<') {
            result += "&lt;";
        } else if (*p == '>') {
            result += "&gt;";
        } else if (*p == '&') {
            result += "&amp;";
        }
        ++p;
        lastp = p;
    }

    // output remaining text after last '<', '>', or '&', or the entire string if these do not occur
    result += std::string_view(lastp, &str.data()[str.size() - 1] - lastp + 1);

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringStrpbrkEncode);

static void StringStrpbrkEncode2(benchmark::State& state) {
  std::string_view str(s);
  for (auto _ : state) {

    // output any '<', '>', or '&', or any text before
    auto p = &str.data()[0];
    auto lastp = p;
    std::string result;
    for (p = strpbrk(p, "<>&"); p != 0 && *p != 0; p = strpbrk(p, "<>&")) {

        // output section before
        result += std::string_view(lastp, p - lastp);

        // output special characters
        if (*p == '<') {
            result += "&lt;"sv;
        } else if (*p == '>') {
            result += "&gt;"sv;
        } else if (*p == '&') {
            result += "&amp;"sv;
        }
        ++p;
        lastp = p;
    }

    // output remaining text after last '<', '>', or '&', or the entire string if these do not occur
    result += std::string_view(lastp, &str.data()[str.size() - 1] - lastp + 1);

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringStrpbrkEncode2);

static void StringStrpbrkEncode3(benchmark::State& state) {
  std::string_view str(s);
  for (auto _ : state) {

    // output any '<', '>', or '&', or any text before
    auto p = &str.data()[0];
    auto lastp = p;
    std::string result;
    for (p = strpbrk(p, "<>&"); p != 0 && *p != 0; p = strpbrk(p, "<>&")) {

        // output section before
        result += std::string_view(lastp, p - lastp);

        // output special characters
        if (*p == '<') {
            for (auto c : "&lt;"sv)
              result += c;
        } else if (*p == '>') {
            for (auto c : "&gt;"sv)
              result += c;
        } else if (*p == '&') {
            for (auto c :  "&amp;"sv)
              result += c;
        }
        ++p;
        lastp = p;
    }

    // output remaining text after last '<', '>', or '&', or the entire string if these do not occur
    result += std::string_view(lastp, &str.data()[str.size() - 1] - lastp + 1);

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringStrpbrkEncode3);

static void StringStrpbrkEncode4(benchmark::State& state) {
  std::string_view str(s);
  for (auto _ : state) {

    // output any '<', '>', or '&', or any text before
    auto p = 0;
    auto lastp = p;
    std::string result;
    for (p = str.find("<>&"sv); p != str.npos; p = str.find("<>&"sv)) {

        // output section before
        result += str.substr(lastp, p - lastp);

        // output special characters
        if (str[p] == '<') {
            for (auto c : "&lt;"sv)
              result += c;
        } else if (str[p] == '>') {
            for (auto c : "&gt;"sv)
              result += c;
        } else if (str[p] == '&') {
            for (auto c :  "&amp;"sv)
              result += c;
        }
        ++p;
        lastp = p;
    }

    // output remaining text after last '<', '>', or '&', or the entire string if these do not occur
    result += str.substr(lastp, str.size() - lastp - 1);

    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(StringStrpbrkEncode4);
