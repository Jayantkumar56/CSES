
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>


class ArrayDescription {
private:
    static constexpr int mod = 1'000'000'000 + 7;

public:
    void Solve()
    {
        std::vector<int> prevIdxResults(i_MaxValue + 1);

        auto currIdxResults = i_Array[0] == 0 ? std::vector(i_MaxValue + 1, 1)
                                              : std::vector(i_MaxValue + 1, 0);

        currIdxResults[i_Array[0]] = 1;
        currIdxResults[0]          = 0;

        for (int i = 1; i < i_ArraySize; ++i)
        {
            std::swap(currIdxResults, prevIdxResults);

            for (auto& result : currIdxResults)
            {
                result = 0;
            }

            const int start = (i_Array[i] != 0) ? i_Array[i] : 1;
            const int end   = (i_Array[i] != 0) ? i_Array[i] : i_MaxValue;


            for (int j = start; j <= end; ++j)
            {
                int64_t result  = static_cast<int64_t>(prevIdxResults[j]);
                result         += static_cast<int64_t>((j - 1 > 0) ? prevIdxResults[j - 1] : 0);
                result += static_cast<int64_t>((j + 1 <= i_MaxValue) ? prevIdxResults[j + 1] : 0);

                result            %= mod;
                currIdxResults[j]  = static_cast<int>(result);
            }
        }

        o_PossibleArraysCount = i_Array.back() != 0 ? currIdxResults[i_Array.back()]
                                                    : std::accumulate(currIdxResults.begin(),
                                                                      currIdxResults.end(),
                                                                      0,
                                                                      [](const int a, const int b)
        {
            return (a + b) % mod;
        });
    }

    void ProcessInput()
    {
        std::cin >> i_ArraySize >> i_MaxValue;

        i_Array.resize(i_ArraySize);

        for (auto& book : i_Array)
        {
            std::cin >> book;
        }
    }

    void ShowOutput()
    {
        std::cout << o_PossibleArraysCount;
    }

private:
    int i_ArraySize;
    int i_MaxValue;

    std::vector<int> i_Array;

    int o_PossibleArraysCount;
};
