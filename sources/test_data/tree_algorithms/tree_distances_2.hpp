
#pragma once


#include <solutions/tree_algorithms/tree_distances_2.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<TreeDistances2> {
    static constexpr std::string_view SolutionName = "TreeDistances2";

    static constexpr CStringArray Inputs = {
        R"(5
1 2
1 3
3 4
3 5
)"sv,
    };

    static constexpr CStringArray Outputs = {"6 9 5 8 8"sv};
};
