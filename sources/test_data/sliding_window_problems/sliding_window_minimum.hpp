
#pragma once


#include <solutions/sliding_window_problems/sliding_window_minimum.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowMinimum> {
    static constexpr std::string_view SolutionName = "Sliding Window Minimum";

    static constexpr CStringArray Inputs = {
        R"(8 5
3 7 1 11
)"sv,
        R"(10000000 1000
333333333 7 1 999999937
)"sv,
        R"(10000000 1000
0 1 1 999999937
)"sv,
        R"(10000000 5000000
333333333 7 1 999999937
)"sv,
    };

    static constexpr CStringArray Outputs = {"3"sv, "8399506"sv, "9999000"sv, "139"sv};
};
