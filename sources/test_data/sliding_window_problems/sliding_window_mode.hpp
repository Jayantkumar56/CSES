
#pragma once


#include <solutions/sliding_window_problems/sliding_window_mode.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowMode> {
    static constexpr std::string_view SolutionName = "Sliding Window Mode";

    static constexpr CStringArray Inputs = {
        R"(8 3
1 2 3 2 5 2 4 4
)"sv,
        R"(100 10
10 9 6 10 10 3 6 7 6 5 7 4 6 2 7 7 2 9 6 7 7 5 1 6 10 2 8 4 3 6 10 8 10 5 4 9 2 9 10 10 1 2 7 10 1 1 4 4 2 5 4 8 10 6 1 10 6 7 10 4 9 1 9 5 4 10 3 9 9 9 3 1 8 10 8 1 9 8 9 6 9 10 5 5 2 3 1 3 6 2 4 8 9 5 1 9 3 7 6 10
)"sv,
    };

    static constexpr CStringArray Outputs = {
        "1 2 2 2 2 4"sv,
        "6 6 6 6 6 6 7 7 7 7 7 7 7 7 7 7 2 6 6 7 6 6 6 10 10 4 4 4 9 10 10 10 10 2 10 10 1 1 1 1 1 4 4 4 4 4 4 4 6 10 10 10 10 1 1 4 4 4 9 9 9 9 9 9 9 9 9 9 8 8 8 8 8 9 9 9 9 5 3 3 2 2 2 2 2 1 1 3 9 9 9"sv};
};
