
#include <iostream>
#include <array>



class DiceCombinations {
private:
    static constexpr auto mod = 1000'000'000 + 7;

public:
    void Solve()
    {
        constexpr int              arraySize = 8;
        std::array<int, arraySize> results{};
        results[0] = 1;

        for (int i = 1; i <= i_Sum; ++i)
        {
            const int currIdx = i % arraySize;
            results[currIdx]  = 0;

            // try every number on dice
            for (int j = std::max(0, i - 6); j < i; ++j)
            {
                results[currIdx] += results[j % arraySize];
                results[currIdx] %= mod;
            }
        }

        o_NumWays = results[i_Sum % arraySize];
    }

    void ProcessInput()
    {
        std::cin >> i_Sum;
    }

    void ShowOutput()
    {
        std::cout << o_NumWays;
    }

private:
    int i_Sum;
    int o_NumWays;
};
