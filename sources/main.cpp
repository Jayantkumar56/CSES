
#include <test_data/tree_algorithms/tree_algorithms.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>



struct FailedTestData {
    int         TestNumber;
    std::string ExpectedOutput;
    std::string ActualOutput;
};

struct TestResult {
    std::string_view            SolutionName{};
    int                         TotalTests = 0;
    int                         TestPassed = 0;
    std::vector<FailedTestData> FailedTests{};

    void Print()
    {
        for (const auto& failedTest : FailedTests)
        {
            std::cout << "Test '" << failedTest.TestNumber << "' Failed!\n";
            std::cout << "Expected  : " << failedTest.ExpectedOutput << "\n";
            std::cout << "Got       : " << failedTest.ActualOutput << "\n";
            std::cout << "--------------------------------------------------------------\n\n";
        }

        std::cout << "\n--------------------------------------------------------------\n";
        std::cout << "Tests ran for '" << SolutionName << "', results are:\n";
        std::cout << "Total tests  : " << TotalTests << "\n";
        std::cout << "Tests passed : " << TestPassed << "\n";
        std::cout << "--------------------------------------------------------------\n\n";
    }
};

template <typename SolutionT>
class TestRunner {
private:
    static constexpr const char* SOLUTION_PATH = "./solution";

private:
    template <typename FunctionT>
    void ForEachDataSet(FunctionT&& func)
    {
        const auto& inputs  = TestData<SolutionT>::Inputs;
        const auto& outputs = TestData<SolutionT>::Outputs;

        static_assert(inputs.size() == outputs.size());

        const std::size_t size = inputs.size();

        for (std::size_t i = 0; i < size; ++i)
        {
            func(inputs[i], outputs[i]);
        }
    }

public:
    TestResult RunTest()
    {
        TestResult results{
            .SolutionName{TestData<SolutionT>::SolutionName},
        };

        int testsPerformed = 0;
        int testsPassed    = 0;

        std::stringstream inputStream;
        std::stringstream outputStream;

        auto* originalCinBuffer  = std::cin.rdbuf();
        auto* originalCoutBuffer = std::cout.rdbuf();

        std::cin.rdbuf(inputStream.rdbuf());
        std::cout.rdbuf(outputStream.rdbuf());

        ForEachDataSet([&](std::string_view input, std::string_view expectedOutput)
        {
            ++testsPerformed;
            inputStream.str(std::string(input));
            inputStream.clear();

            outputStream.str("");
            outputStream.clear();

            SolutionT solution;
            solution.ProcessInput();
            solution.Solve();
            solution.ShowOutput();

            std::cout.flush();
            std::string actualOutput = outputStream.str();

            if (Trim(actualOutput) == Trim(expectedOutput))
            {
                ++testsPassed;
            }
            else
            {
                results.FailedTests.emplace_back(testsPerformed,
                                                 std::string(expectedOutput),
                                                 std::move(actualOutput));
            }
        });

        std::cin.rdbuf(originalCinBuffer);
        std::cout.rdbuf(originalCoutBuffer);

        results.TotalTests = testsPerformed;
        results.TestPassed = testsPassed;

        return results;
    }

private:
    std::string_view Trim(std::string_view str)
    {
        // Trim leading whitespace
        auto start = std::ranges::find_if(str.begin(),
                                          str.end(),
                                          [](unsigned char ch)
        {
            return !std::isspace(ch);
        });

        // Trim trailing whitespace
        auto end = std::ranges::find_if(str.rbegin(),
                                        str.rend(),
                                        [](unsigned char ch)
        {
            return !std::isspace(ch);
        });

        if (start >= end.base())
        {
            return "";
        }

        return {start, end.base()};
    }
};

int main()
{
    TestRunner<TreeMatching> testRunner{};

    TestResult testResults = testRunner.RunTest();
    testResults.Print();
}
