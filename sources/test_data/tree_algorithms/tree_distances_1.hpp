
#pragma once


#include <solutions/tree_algorithms/tree_distances_1.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<TreeDistances1> {
    static constexpr std::string_view SolutionName = "TreeDistances1";

    static constexpr CStringArray Inputs = {
        R"(5
1 2
1 3
3 4
3 5
)"sv,
        R"(10
9 7
8 10
3 6
7 1
4 9
3 5
10 4
5 2
8 6
)"sv,
        R"(10
5 7
4 2
9 7
6 1
9 4
3 2
3 8
10 6
10 5
)"sv,
        R"(10
10 2
3 4
5 7
6 1
6 5
10 7
4 8
3 1
9 8
)"sv,
    };

    static constexpr CStringArray Outputs = {"2 3 2 3 3"sv,
                                             "9 9 7 6 8 6 8 5 7 5"sv,
                                             "9 7 8 6 6 8 5 9 5 7"sv,
                                             "5 9 6 7 6 5 7 8 9 8"sv};
};
