
#include <iostream>
#include <vector>
#include <cstdint>
#include <numeric>



class SlidingWindowSum {
private:
    std::vector<std::int64_t> GenerateArray() const
    {
        std::vector<std::int64_t> array(i_ArraySize, i_x);

        const std::int64_t a = i_a % i_c;
        const std::int64_t b = i_b % i_c;
        const std::int64_t c = i_c;

        std::partial_sum(array.cbegin(),
                         array.cend(),
                         array.begin(),
                         [a, b, c](std::int64_t prev, std::int64_t)
        {
            return (((a * prev) % c) + b) % c;
        });

        return array;
    }

public:
    void Solve()
    {
        std::vector<std::int64_t> array = GenerateArray();

        std::int64_t sumK = std::accumulate(array.cbegin(),
                                            array.cbegin() + i_SubarrSize,
                                            std::int64_t{0});

        o_Sum = sumK;

        for (size_t i = 0, j = i_SubarrSize; j < i_ArraySize; ++i, ++j)
        {
            sumK   = sumK + array[j] - array[i];
            o_Sum ^= sumK;
        }
    }

    void ProcessInput()
    {
        std::cin >> i_ArraySize >> i_SubarrSize;
        std::cin >> i_x >> i_a >> i_b >> i_c;
    }

    void ShowOutput()
    {
        std::cout << o_Sum;
    }

private:
    std::size_t i_ArraySize;  // n
    std::size_t i_SubarrSize; // k

    std::uint64_t i_x;
    std::uint64_t i_a;
    std::uint64_t i_b;
    std::uint64_t i_c;

    std::uint64_t o_Sum; // xor sum of all windows
};
