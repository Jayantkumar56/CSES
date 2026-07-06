
#include <iostream>
#include <cstdint>
#include <vector>
#include <array>
#include <memory>



class SlidingWindowOR {
private:
    void Approach1()
    {
        o_SumXOR = 0;

        std::vector<std::int64_t> numbers(i_SubarrSize);
        std::array<int, 32>       orBits{};

        // first k elements (first window)
        {
            numbers[0] = i_x;

            for (size_t i = 0; i < orBits.size(); ++i)
            {
                orBits[i] += (numbers[0] >> i) & 1;
            }

            for (std::int64_t i = 1; i < i_SubarrSize; ++i)
            {
                numbers[i] = (numbers[i - 1] * i_a + i_b) % i_c;

                for (size_t j = 0; j < orBits.size(); ++j)
                {
                    orBits[j] += (numbers[i] >> j) & 1;
                }
            }

            for (size_t i = 0; i < orBits.size(); ++i)
            {
                o_SumXOR |= static_cast<int>(orBits[i] > 0) << i;
            }
        }

        // rest of the windows
        {
            std::int64_t startIdx = 0;
            std::int64_t endIdx   = i_SubarrSize - 1;

            for (std::int64_t i = i_SubarrSize; i < i_ArraySize; ++i)
            {
                const std::int64_t current  = (numbers[endIdx] * i_a + i_b) % i_c;
                const std::int64_t numStart = numbers[startIdx];

                ++startIdx;
                ++endIdx;
                endIdx   = (endIdx < i_SubarrSize) ? endIdx : endIdx - i_SubarrSize;
                startIdx = (startIdx < i_SubarrSize) ? startIdx : startIdx - i_SubarrSize;

                numbers[endIdx] = current;

                for (size_t j = 0; j < orBits.size(); ++j)
                {
                    orBits[j] += ((current >> j) & 1) - ((numStart >> j) & 1);
                    o_SumXOR  ^= static_cast<int>(orBits[j] > 0) << j;
                }
            }
        }
    }

    void Approach2()
    {
        auto numbers = std::make_unique_for_overwrite<int[]>(i_ArraySize);
        auto prefix  = std::make_unique_for_overwrite<int[]>(i_ArraySize);
        auto suffix  = std::make_unique_for_overwrite<int[]>(i_ArraySize);

        numbers[0]           = i_x;
        prefix[0]            = i_x;
        std::int64_t current = i_x;

        for (std::int64_t i = 1; i < i_ArraySize; ++i)
        {
            current    = (current * i_a + i_b) % i_c;
            numbers[i] = static_cast<int>(current);
            prefix[i]  = (i % i_SubarrSize == 0) ? numbers[i] : numbers[i] | prefix[i - 1];
        }

        suffix[i_ArraySize - 1] = numbers[i_ArraySize - 1];

        for (std::int64_t i = i_ArraySize - 2; i >= 0; --i)
        {
            suffix[i] = (i % i_SubarrSize == 0) ? 0 : numbers[i] | suffix[i + 1];
        }

        o_SumXOR = 0;

        for (std::int64_t i = i_SubarrSize - 1; i < i_ArraySize; ++i)
        {
            const int currOr  = prefix[i] | suffix[i - i_SubarrSize + 1];
            o_SumXOR         ^= currOr;
        }
    }

public:
    void Solve()
    {
        Approach2();
    }

    void ProcessInput()
    {
        std::cin >> i_ArraySize >> i_SubarrSize;
        std::cin >> i_x >> i_a >> i_b >> i_c;
    }

    void ShowOutput()
    {
        std::cout << o_SumXOR;
    }

private:
    std::int64_t i_ArraySize;  // n
    std::int64_t i_SubarrSize; // k

    std::int64_t i_x;
    std::int64_t i_a;
    std::int64_t i_b;
    std::int64_t i_c;

    int o_SumXOR; // xor sum of all windows
};
