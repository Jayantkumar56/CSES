
#pragma once


#include <solutions/tree_algorithms/tree_diameter.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<TreeDiameter> {
    static constexpr std::string_view SolutionName = "TreeDiameter";

    static constexpr CStringArray Inputs = {
        R"(5
1 2
1 3
3 4
3 5
)"sv,
    };

    static constexpr CStringArray Outputs = {"3"sv};
};
