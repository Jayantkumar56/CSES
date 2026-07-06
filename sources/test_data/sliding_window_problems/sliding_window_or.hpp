
#pragma once


#include <solutions/sliding_window_problems/sliding_window_or.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowOR> {
    static constexpr std::string_view SolutionName = "Sliding Window OR";

    static constexpr CStringArray Inputs = {
        R"(8 5
3 7 1 11
)"sv,
        R"(100 20
3 7 1 997
)"sv,
        R"(10000000 1000
333333333 7 1 999999937
)"sv,
        R"(10000000 1000
0 1 1 999983
)"sv,
        R"(10000000 1
1000000000 1000000000 1000000000 998244353
)"sv,
        R"(10000000 1000
0 1 1 999999937
)"sv,
    };

    static constexpr CStringArray Outputs = {
        "4"sv,
        "1023"sv,
        "1073741823"sv,
        "1000447"sv,
        "860642281"sv,
        "5000191"sv,
    };
};
