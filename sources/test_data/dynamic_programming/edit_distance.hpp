
#pragma once


#include <solutions/dynamic_programming/edit_distance.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<EditDistance> {
    static constexpr std::string_view SolutionName = "Edit Distance";

    static constexpr CStringArray Inputs = {
        R"(LOVE
MOVIE
)"sv,
    };

    static constexpr CStringArray Outputs = {"2"sv};
};
