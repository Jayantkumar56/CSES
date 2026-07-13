
#pragma once


#include <solutions/dynamic_programming/dice_combinations.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<DiceCombinations> {
    static constexpr std::string_view SolutionName = "Dice Combinations";

    static constexpr CStringArray Inputs = {
        R"(3
)"sv,
        R"(40
)"sv,
        R"(999997
)"sv};

    static constexpr CStringArray Outputs = {"4"sv, "567401756"sv, "74225807"sv};
};
