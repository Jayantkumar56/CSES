
#pragma once


#include <solutions/sliding_window_problems/sliding_window_distinct_values.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowDistinctValues> {
    static constexpr std::string_view SolutionName = "Sliding Window Distinct Values";

    static constexpr CStringArray Inputs = {
        R"(8 3
1 2 3 2 5 2 2 2
)"sv,
    };

    static constexpr CStringArray Outputs = {"3 2 3 2 2 1"sv};
};
