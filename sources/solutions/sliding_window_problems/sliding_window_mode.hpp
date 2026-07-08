
#include <algorithm>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <ranges>



class MinHeap {
public:
    void Reserve(int length)
    {
        m_Data.reserve(length);
        m_Indices.reserve(length + (length >> 2));
    }

    void IncrementFreq(int key)
    {
        const auto idxItr = m_Indices.find(key);
        int        idx    = 0;

        if (idxItr == m_Indices.end())
        {
            m_Data.emplace_back(key, 1);
            idx            = static_cast<int>(m_Data.size() - 1);
            m_Indices[key] = idx;
        }
        else
        {
            idx                = idxItr->second;
            m_Data[idx].second = m_Data[idx].second + 1;
        }

        HeapifyUpward(idx);
    }

    void DecrementFreq(int key)
    {
        const auto idxItr = m_Indices.find(key);

        if (idxItr == m_Indices.end())
        {
            return;
        }

        const int idx      = idxItr->second;
        m_Data[idx].second = m_Data[idx].second - 1;

        if (m_Data[idx].second == 0)
        {
            SwapElements(idx, static_cast<int>(m_Data.size() - 1));
            m_Data.pop_back();
            m_Indices.erase(key);
        }

        HeapifyDownward(idx);
    }

    int GetFront()
    {
        if (m_Data.size() == 0)
        {
            return 0;
        }

        return m_Data[0].first;
    }

private:
    void HeapifyDownward(int idx)
    {
        while (idx < static_cast<int>(m_Data.size()))
        {
            const int child1Idx = (idx << 1) + 1;
            const int child2Idx = (idx << 1) + 2;

            int idxToMoveTo = idx;

            if (child1Idx < static_cast<int>(m_Data.size()))
            {
                const auto& child = m_Data[child1Idx];
                const auto& curr  = m_Data[idxToMoveTo];

                if ((child.second > curr.second) ||
                    (child.second == curr.second && child.first < curr.first))
                {
                    idxToMoveTo = child1Idx;
                }
            }

            if (child2Idx < static_cast<int>(m_Data.size()))
            {
                const auto& child = m_Data[child2Idx];
                const auto& curr  = m_Data[idxToMoveTo];

                if ((child.second > curr.second) ||
                    (child.second == curr.second && child.first < curr.first))
                {
                    idxToMoveTo = child2Idx;
                }
            }

            if (idx == idxToMoveTo)
            {
                break;
            }

            SwapElements(idx, idxToMoveTo);
            idx = idxToMoveTo;
        }
    }

    void HeapifyUpward(int idx)
    {
        while (idx > 0)
        {
            const int parentIdx = (idx - 1) >> 1;

            const auto& current = m_Data[idx];
            const auto& parent  = m_Data[parentIdx];

            if ((current.second > parent.second) ||
                (current.second == parent.second && current.first < parent.first))
            {
                SwapElements(idx, parentIdx);
                idx = parentIdx;
            }
            else
            {
                break;
            }
        }
    }

    void SwapElements(int idx1, int idx2)
    {
        std::swap(m_Data[idx1], m_Data[idx2]);
        m_Indices[m_Data[idx1].first] = idx1;
        m_Indices[m_Data[idx2].first] = idx2;
    }

private:
    std::unordered_map<int, int>     m_Indices;
    std::vector<std::pair<int, int>> m_Data;
};

class SlidingWindowMode {
public:
    void Solve()
    {
        MinHeap queue;
        queue.Reserve(i_SubarraySize);

        std::ranges::for_each(i_Array | std::views::take(i_SubarraySize),
                              [&queue](int value)
        {
            queue.IncrementFreq(value);
        });

        o_Results.reserve(i_ArraySize - i_SubarraySize + 1);
        o_Results.push_back(queue.GetFront());

        for (int i = 0, j = i_SubarraySize; j < i_ArraySize; ++i, ++j)
        {
            queue.DecrementFreq(i_Array[i]);
            queue.IncrementFreq(i_Array[j]);
            o_Results.push_back(queue.GetFront());
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
