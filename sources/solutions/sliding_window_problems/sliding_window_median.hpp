
#include <ranges>
#include <iostream>
#include <vector>
#include <set>



class SlidingWindowMedian {
public:
    void Solve()
    {
        std::multiset<int> set1;
        std::multiset<int> set2;

        const size_t set1Size = static_cast<size_t>((i_SubarraySize - 1) >> 1);

        for (const int value : i_Array | std::views::take(i_SubarraySize))
        {
            set1.insert(value);

            if (set1.size() > set1Size)
            {
                auto set1Back = --set1.end();
                set2.insert(*set1Back);
                set1.erase(set1Back);
            }
        }

        o_Results.reserve(i_SubarraySize);
        o_Results.push_back(*set2.begin());

        for (int i = 0, j = i_SubarraySize; j < i_ArraySize; ++i, ++j)
        {
            if (set1.contains(i_Array[i]))
            {
                set1.erase(set1.find(i_Array[i]));
                set1.insert(i_Array[j]);

                auto set1Back = --set1.end();

                if (*set1Back > *set2.begin())
                {
                    set2.insert(*set1Back);
                    set1.erase(set1Back);
                    set1.insert(*set2.begin());
                    set2.erase(set2.begin());
                }
            }
            else if (set2.contains(i_Array[i]))
            {
                set2.erase(set2.find(i_Array[i]));
                set1.insert(i_Array[j]);

                auto set1Back = --set1.end();
                set2.insert(*set1Back);
                set1.erase(set1Back);
            }

            o_Results.push_back(*set2.begin());
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
