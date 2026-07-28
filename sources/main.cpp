
#include <test_data/tree_algorithms/tree_algorithms.hpp>
#include <test_data/sliding_window_problems/sliding_window_problems.hpp>
#include <test_data/dynamic_programming/dynamic_programming.hpp>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>



struct SingleTestResult {
    int    TestNumber       = 0;
    bool   Passed           = false;
    double TimeTakenSeconds = 0.0;

    std::string ExpectedOutput;
    std::string ActualOutput;
};

struct TestResult {
    std::string_view              SolutionName{};
    int                           TotalTests       = 0;
    int                           TestPassed       = 0;
    double                        TotalTimeSeconds = 0.0;
    std::vector<SingleTestResult> Tests{};

    void Print()
    {
        std::cout << std::fixed << std::setprecision(6);

        for (const auto& test : Tests)
        {
            std::cout << "Test " << test.TestNumber << " : " << (test.Passed ? "PASS" : "FAIL")
                      << " (" << test.TimeTakenSeconds << " s)\n";

            if (!test.Passed)
            {
                if (test.ExpectedOutput.size() < 300)
                {
                    std::cout << "Expected : " << test.ExpectedOutput << '\n';
                }
                else
                {
                    std::cout << "Expected : " << test.ExpectedOutput.substr(0, 50) << "...\n";
                }

                if (test.ActualOutput.size() < 300)
                {
                    std::cout << "Got      : " << test.ActualOutput << '\n';
                }
                else
                {
                    std::cout << "Got      : " << test.ActualOutput.substr(0, 50) << "...\n";
                }
            }

            std::cout << "--------------------------------------------------------------\n";
        }

        std::cout << "\n==============================================================\n";
        std::cout << "Results for '" << SolutionName << "'\n";
        std::cout << "--------------------------------------------------------------\n";
        std::cout << "Total tests : " << TotalTests << '\n';
        std::cout << "Passed      : " << TestPassed << '\n';
        std::cout << "Failed      : " << (TotalTests - TestPassed) << '\n';
        std::cout << "Total time  : " << TotalTimeSeconds << " s\n";
        std::cout << "Average     : " << (TotalTests ? TotalTimeSeconds / TotalTests : 0.0)
                  << " s/test\n";
        std::cout << "==============================================================\n";
    }
};

template <typename SolutionT>
class TestRunner {
private:
    using Clock = std::chrono::steady_clock;

private:
    template <typename FunctionT>
    void ForEachDataSet(FunctionT&& func)
    {
        const auto& inputs  = TestData<SolutionT>::Inputs;
        const auto& outputs = TestData<SolutionT>::Outputs;

        static_assert(inputs.size() == outputs.size());

        for (std::size_t i = 0; i < inputs.size(); ++i)
        {
            func(inputs[i], outputs[i]);
        }
    }

public:
    TestResult RunTest()
    {
        TestResult results{
            .SolutionName = TestData<SolutionT>::SolutionName,
        };

        std::stringstream inputStream;
        std::stringstream outputStream;

        auto* originalCinBuffer  = std::cin.rdbuf();
        auto* originalCoutBuffer = std::cout.rdbuf();

        std::cin.rdbuf(inputStream.rdbuf());
        std::cout.rdbuf(outputStream.rdbuf());

        int testsPerformed = 0;
        int testsPassed    = 0;

        ForEachDataSet([&](std::string_view input, std::string_view expectedOutput) {
            ++testsPerformed;

            inputStream.str(std::string(input));
            inputStream.clear();

            outputStream.str("");
            outputStream.clear();

            auto start = Clock::now();

            SolutionT solution;
            solution.ProcessInput();
            solution.Solve();
            solution.ShowOutput();

            auto end = Clock::now();

            std::cout.flush();

            const double elapsed = std::chrono::duration<double>(end - start).count();

            results.TotalTimeSeconds += elapsed;

            std::string actualOutput = outputStream.str();

            const bool passed = Trim(actualOutput) == Trim(expectedOutput);

            if (passed)
            {
                ++testsPassed;
            }

            results.Tests.emplace_back(testsPerformed,
                                       passed,
                                       elapsed,
                                       std::string(expectedOutput),
                                       std::move(actualOutput));
        });

        std::cin.rdbuf(originalCinBuffer);
        std::cout.rdbuf(originalCoutBuffer);

        results.TotalTests = testsPerformed;
        results.TestPassed = testsPassed;

        return results;
    }

private:
    static std::string_view Trim(std::string_view str)
    {
        auto start = std::ranges::find_if(str, [](unsigned char ch) {
            return !std::isspace(ch);
        });

        auto end = std::ranges::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        });

        if (start >= end.base())
        {
            return {};
        }

        return {start, end.base()};
    }
};

int main()
{
    TestRunner<EditDistance> testRunner;

    TestResult testResults = testRunner.RunTest();
    testResults.Print();
}
