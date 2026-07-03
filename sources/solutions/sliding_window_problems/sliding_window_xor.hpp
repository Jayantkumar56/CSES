
#include <iostream>
#include <cstdint>



class SlidingWindowXOR {
public:
    void Solve()
    {
        std::int64_t current = i_x;
        o_SumXOR             = i_x;

        for (std::int64_t i = 1; i < i_SubarrSize - 1; ++i)
        {
            current   = (current * i_a + i_b) % i_c;
            o_SumXOR ^= ((i + 1) & 1) * current;
        }

        {
            const std::int64_t lowerBound = i_SubarrSize == 1 ? 1 : i_SubarrSize - 1;
            const std::int64_t upperBound = i_ArraySize - i_SubarrSize;
            const std::int64_t count      = i_SubarrSize & 1;

            for (std::int64_t i = lowerBound; i <= upperBound; ++i)
            {
                current   = (current * i_a + i_b) % i_c;
                o_SumXOR ^= count * current;
            }
        }

        {
            const std::int64_t lowerBound = i_ArraySize - i_SubarrSize + 1;
            const std::int64_t upperBound = i_ArraySize - 1;

            std::int64_t count = i_SubarrSize - 1;

            for (std::int64_t i = lowerBound; i <= upperBound; ++i)
            {
                current   = (current * i_a + i_b) % i_c;
                o_SumXOR ^= (count-- & 1) * current;
            }
        }
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

    std::uint64_t i_x;
    std::uint64_t i_a;
    std::uint64_t i_b;
    std::uint64_t i_c;

    std::uint64_t o_SumXOR; // xor sum of all windows
};
