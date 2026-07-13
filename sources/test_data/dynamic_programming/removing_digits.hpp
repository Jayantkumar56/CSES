
#pragma once


#include <solutions/dynamic_programming/removing_digits.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<RemovingDigits> {
    static constexpr std::string_view SolutionName = "Removing Digits";

    static constexpr CStringArray Inputs = {
        R"(27
)"sv,
    };

    static constexpr CStringArray Outputs = {"5"sv};
};
