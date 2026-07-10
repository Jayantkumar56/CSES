
#include <ranges>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>



class SlidingWindowMex {
public:
    void Solve()
    {
        std::unordered_map<int, int> freqMap;
        freqMap.reserve(i_SubarraySize + (i_SubarraySize >> 4));

        auto          elements = std::ranges::views::iota(0, i_SubarraySize + 1);
        std::set<int> availableElements(elements.begin(), elements.end());

        for (const int val : i_Array | std::views::take(i_SubarraySize))
        {
            ++freqMap[val];

            if (availableElements.contains(val))
            {
                availableElements.erase(val);
            }
        }

        o_Results.reserve(i_ArraySize - i_SubarraySize + 1);
        o_Results.push_back(*availableElements.begin());

        for (int i = 0, j = i_SubarraySize; j < i_ArraySize; ++i, ++j)
        {
            auto startElementItr = freqMap.find(i_Array[i]);

            if (startElementItr->second == 1)
            {
                availableElements.insert(startElementItr->first);
                freqMap.erase(startElementItr);
            }
            else
            {
                --startElementItr->second;
            }

            ++freqMap[i_Array[j]];

            if (availableElements.contains(i_Array[j]))
            {
                availableElements.erase(i_Array[j]);
            }

            o_Results.push_back(*availableElements.begin());
        }
    }

    void ProcessInput()
    {
        std::cin >> i_ArraySize >> i_SubarraySize;

        i_Array = std::vector<int>(i_ArraySize);

        for (int i = 0; i < i_ArraySize; ++i)
        {
            std::cin >> i_Array[i];
        }
    }

    void ShowOutput()
    {
        for (const int result : o_Results)
        {
            std::cout << result << " ";
        }
    }

private:
    int i_ArraySize;
    int i_SubarraySize;

    std::vector<int> i_Array;

    std::vector<int> o_Results;
};
