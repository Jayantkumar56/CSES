
#pragma once


#include <solutions/tree_algorithms/distance_queries.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<DistanceQueries> {
    static constexpr std::string_view SolutionName = "Distance Queries";

    static constexpr CStringArray Inputs = {
        R"(5 3
1 2
1 3
3 4
3 5
1 3
2 5
1 4
)"sv,
        R"(10 10
7 10
4 8
6 2
4 3
7 5
10 3
5 1
6 1
2 9
3 4
4 3
4 4
8 10
6 4
2 8
6 4
5 9
5 9
5 9
)"sv,
    };

    static constexpr CStringArray Outputs = {
        R"(1
3
2
)"sv,
        R"(1
1
0
3
6
8
6
4
4
4
)"sv,
    };
};
