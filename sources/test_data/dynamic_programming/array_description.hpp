
#pragma once


#include <solutions/dynamic_programming/array_description.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<ArrayDescription> {
    static constexpr std::string_view SolutionName = "Book Shop";

    static constexpr CStringArray Inputs = {
        R"(3 5
2 0 2
)"sv,
        R"(10 3
0 0 0 0 0 0 0 0 0 0
)"sv,
        R"(2 3
0 0
)"sv,
        R"(1 3
0
)"sv,
    };

    static constexpr CStringArray Outputs = {"3"sv, "8119"sv, "7"sv, "3"sv};
};
