
#include <iostream>
#include <vector>
#include <cstdint>



class SlidingWindowMinimum {
private:
    struct Node {
        int Value;
        int Index;
    };

public:
    void Solve()
    {
        std::vector<Node> queue(i_SubarrSize);

        int start = 0;
        int end   = 0;

        int startSlot = 0;
        int endSlot   = 0;

        int currentElement = i_x;

        for (int i = 0; i < i_ArraySize; ++i)
        {
            while (start < end && queue[startSlot].Index + i_SubarrSize <= i)
            {
                ++start;
                ++startSlot;

                if (startSlot == i_SubarrSize)
                {
                    startSlot = 0;
                }
            }

            while (end > start)
            {
                int backSlot = endSlot - 1;
                if (backSlot < 0)
                {
                    backSlot = i_SubarrSize - 1;
                }

                if (queue[backSlot].Value < currentElement)
                {
                    break;
                }

                --end;
                endSlot = backSlot;
            }

            queue[endSlot] = {.Value = currentElement, .Index = i};

            ++end;
            ++endSlot;

            if (endSlot == i_SubarrSize)
            {
                endSlot = 0;
            }

            if (i >= i_SubarrSize - 1)
            {
                o_MinXOR ^= queue[startSlot].Value;
            }

            currentElement = (i_a * currentElement + i_b) % i_c;
        }
    }

    void ProcessInput()
    {
        std::cin >> i_ArraySize >> i_SubarrSize;
        std::cin >> i_x >> i_a >> i_b >> i_c;
    }

    void ShowOutput()
    {
        std::cout << o_MinXOR;
    }

private:
    int i_ArraySize;  // n
    int i_SubarrSize; // k

    std::int64_t i_x;
    std::int64_t i_a;
    std::int64_t i_b;
    std::int64_t i_c;

    std::int64_t o_MinXOR = 0; // xor sum of all windows
};
