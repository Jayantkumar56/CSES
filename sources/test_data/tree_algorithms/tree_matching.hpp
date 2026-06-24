
#include <solutions/tree_algorithms/tree_matching.hpp>
#include <test_data/test_data.hpp>



template <>
struct TestData<TreeMatching> {
    static constexpr std::string_view SolutionName = "TreeMatching";

    static constexpr CStringArray Inputs = {
        R"(5
1 2
1 3
3 4
3 5
)"sv,
    };

    static constexpr CStringArray Outputs = {"2"sv};
};

