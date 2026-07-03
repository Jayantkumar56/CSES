
#pragma once


#include <solutions/sliding_window_problems/sliding_window_xor.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<SlidingWindowXOR> {
    static constexpr std::string_view SolutionName = "Sliding Window XOR";

    static constexpr CStringArray Inputs = {
        R"(8 5
3 7 1 11
)"sv,
        R"(10000000 5000000
333333333 7 1 999999937
)"sv,
        R"(2 1
2 3 4 5
)"sv,
    };

    static constexpr CStringArray Outputs = {"0"sv, "62874861"sv, "2"sv};
};
