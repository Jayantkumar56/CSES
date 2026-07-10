
#pragma once


#include <solutions/sliding_window_problems/sliding_window_median.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowMedian> {
    static constexpr std::string_view SolutionName = "Sliding Window Mex";

    static constexpr CStringArray Inputs = {
        R"(8 3
2 4 3 5 8 1 2 1
)"sv,
        R"(10 2
4 4 3 2 10 1 2 7 10 2
)"sv,
    };

    static constexpr CStringArray Outputs = {"3 4 5 5 2 1"sv, "4 3 2 2 1 1 2 7 2"sv};
};
