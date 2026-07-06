
#include <iostream>
#include <memory>
#include <unordered_map>



class SlidingWindowDistinctValues {
public:
    void Solve()
    {
        std::unordered_map<int, int> freqency;
        freqency.reserve(i_SubarraySize + i_SubarraySize / 4);

        for (int i = 0; i < i_SubarraySize; ++i)
        {
            ++freqency[i_Array[i]];
        }

        o_Results[0] = static_cast<int>(freqency.size());

        for (int i = i_SubarraySize; i < i_ArraySize; ++i)
        {
            if (--freqency[i_Array[i - i_SubarraySize]] == 0)
            {
                freqency.erase(i_Array[i - i_SubarraySize]);
            }

            ++freqency[i_Array[i]];
            o_Results[i - i_SubarraySize + 1] = static_cast<int>(freqency.size());
        }
    }

    void ProcessInput()
    {
        std::cin >> i_ArraySize >> i_SubarraySize;
        o_ResultsSize = i_ArraySize - i_SubarraySize + 1;

        o_Results = std::make_unique_for_overwrite<int[]>(o_ResultsSize);
        i_Array   = std::make_unique_for_overwrite<int[]>(i_ArraySize);

        for (int i = 0; i < i_ArraySize; ++i)
        {
            std::cin >> i_Array[i];
        }
    }

    void ShowOutput()
    {
        for (int i = 0; i < o_ResultsSize; ++i)
        {
            std::cout << o_Results[i] << " ";
        }
    }

private:
    int i_ArraySize;
    int i_SubarraySize;

    std::unique_ptr<int[]> i_Array;

    int                    o_ResultsSize;
    std::unique_ptr<int[]> o_Results;
};
