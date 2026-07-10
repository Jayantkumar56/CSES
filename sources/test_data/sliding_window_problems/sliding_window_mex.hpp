
#pragma once


#include <solutions/sliding_window_problems/sliding_window_mex.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowMex> {
    static constexpr std::string_view SolutionName = "Sliding Window Mex";

    static constexpr CStringArray Inputs = {
        R"(8 3
1 2 1 0 5 1 1 0
)"sv,
    };

    static constexpr CStringArray Outputs = {"0 3 2 2 0 2"sv};
};
