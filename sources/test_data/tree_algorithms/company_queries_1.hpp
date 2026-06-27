
#pragma once


#include <solutions/tree_algorithms/company_queries_1.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<CompanyQueries1> {
    static constexpr std::string_view SolutionName = "CompanyQueries1";

    static constexpr CStringArray Inputs = {
        R"(5 3
1 1 3 3
4 1
4 2
4 3
)"sv,
    };

    static constexpr CStringArray Outputs = {
        R"(3
1
-1)"sv,
    };
};
