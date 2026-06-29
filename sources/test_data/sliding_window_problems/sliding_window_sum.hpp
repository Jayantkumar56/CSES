
#pragma once


#include <solutions/sliding_window_problems/sliding_window_sum.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowSum> {
    static constexpr std::string_view SolutionName = "Sliding Window Sum";

    static constexpr CStringArray Inputs = {
        R"(8 5
3 7 1 11
)"sv,
    };

    static constexpr CStringArray Outputs = {"12"sv};
};
