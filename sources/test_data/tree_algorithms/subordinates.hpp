
#pragma once


#include <solutions/tree_algorithms/subordinates.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<Subordinates> {
    static constexpr std::string_view SolutionName = "Subordinates";

    static constexpr CStringArray Inputs = {
        R"(5
1 1 2 3)"sv,
    };

    static constexpr CStringArray Outputs = {"4 1 1 0 0"sv};
};
