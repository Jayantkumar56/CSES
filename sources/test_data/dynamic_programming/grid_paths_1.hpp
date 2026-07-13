
#pragma once


#include <solutions/dynamic_programming/grid_paths_1.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<GridPaths1> {
    static constexpr std::string_view SolutionName = "Grid Paths 1";

    static constexpr CStringArray Inputs = {
        R"(4
....
.*..
...*
*...
)"sv,
    };

    static constexpr CStringArray Outputs = {"3"sv};
};
