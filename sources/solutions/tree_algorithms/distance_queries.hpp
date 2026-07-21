
#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <queue>



class DistanceQueries {
private:
    static constexpr int c_BinaryLiftingDimension = []() {
        const int maxNodeCount = 200'000;

        auto shifts = std::ranges::views::iota(0) | std::views::take_while([](int value) {
                          return maxNodeCount >> value;
                      });

        return 1 + std::ranges::distance(shifts);
    }();

private:
    std::vector<std::vector<int>> CreateAdjList() const
    {
        std::vector<std::vector<int>> adjList(i_NumNodes);

        for (const auto& [nodeA, nodeB] : i_Edges)
        {
            adjList[nodeA - 1].push_back(nodeB - 1);
            adjList[nodeB - 1].push_back(nodeA - 1);
        }

        return adjList;
    }

    std::pair<std::vector<int>, std::vector<int>> GetDepths() const
    {
        std::pair result{std::vector(i_NumNodes, 0), std::vector(i_NumNodes, -1)};

        auto& [depths, parents] = result;
        const auto adjList      = CreateAdjList();

        std::vector<bool> visited(i_NumNodes);
        std::queue<int>   processingQueue;

        visited[0] = true;
        processingQueue.push(0);

        int currDepth = 0;

        while (!processingQueue.empty())
        {
            for (int i = static_cast<int>(processingQueue.size()); i > 0; --i)
            {
                const int currNode = processingQueue.front();
                processingQueue.pop();

                depths[currNode] = currDepth;

                for (const auto& child : adjList[currNode])
                {
                    if (visited[child])
                    {
                        continue;
                    }

                    parents[child] = currNode;
                    processingQueue.push(child);
                    visited[child] = true;
                }
            }

            ++currDepth;
        }

        return result;
    }

    std::vector<std::vector<int>> GetBinaryLifting(const std::vector<int>& parents) const
    {
        std::vector binaryLifting(i_NumNodes, std::vector(c_BinaryLiftingDimension, -1));

        for (int i = 0; i < i_NumNodes; ++i)
        {
            binaryLifting[i][0] = parents[i];
        }

        for (int i = 1; i < c_BinaryLiftingDimension; ++i)
        {
            bool modified = false;

            for (int j = 1; j < i_NumNodes; ++j)
            {
                const int jminusOneParent = binaryLifting[j][i - 1];

                if (jminusOneParent == -1)
                {
                    continue;
                }

                modified            = true;
                binaryLifting[j][i] = binaryLifting[jminusOneParent][i - 1];
            }

            if (!modified)
            {
                break;
            }
        }

        return binaryLifting;
    }

    int LiftNode(int                                  node,
                 int                                  levelsToLift,
                 const std::vector<std::vector<int>>& binaryLifting) const noexcept
    {
        for (int i = 0; i < 32; ++i)
        {
            if (!(levelsToLift & (1 << i)))
            {
                continue;
            }

            node = binaryLifting[node][i];
        }

        return node;
    }

    int GetLCA(int                                  nodeA,
               int                                  nodeB,
               const std::vector<int>&              depths,
               const std::vector<std::vector<int>>& binaryLifting) const noexcept
    {
        if (depths[nodeA] != depths[nodeB])
        {
            const int higherDepthNode = depths[nodeA] > depths[nodeB] ? nodeA : nodeB;
            const int lowerDepthNode  = depths[nodeA] < depths[nodeB] ? nodeA : nodeB;

            const int depthDifference = depths[higherDepthNode] - depths[lowerDepthNode];
            const int liftedNode      = LiftNode(higherDepthNode, depthDifference, binaryLifting);

            nodeA = liftedNode;
            nodeB = lowerDepthNode;
        }

        if (nodeA == nodeB)
        {
            return nodeA;
        }

        while (binaryLifting[nodeA][0] != binaryLifting[nodeB][0])
        {
            int idx = 0;

            while (idx < c_BinaryLiftingDimension - 1
                   && binaryLifting[nodeA][idx + 1] != binaryLifting[nodeB][idx + 1])
            {
                ++idx;
            }

            nodeA = binaryLifting[nodeA][idx];
            nodeB = binaryLifting[nodeB][idx];
        }

        return binaryLifting[nodeA][0];
    }

public:
    void Solve()
    {
        const auto& [depths, parents] = GetDepths();
        const auto binaryLifting      = GetBinaryLifting(parents);

        auto queryResultFn = [&](const std::pair<int, int>& query) {
            const int nodeA = query.first - 1;
            const int nodeB = query.second - 1;

            int lca = GetLCA(nodeA, nodeB, depths, binaryLifting);

            return depths[nodeA] + depths[nodeB] - (depths[lca] << 1);
        };

        o_QueryResults         = std::vector(i_NumQueries, 0);
        const auto resultRange = i_Queries | std::views::transform(queryResultFn);

        std::ranges::copy(resultRange.begin(), resultRange.end(), o_QueryResults.begin());
    }

    void ProcessInput()
    {
        std::cin >> i_NumNodes >> i_NumQueries;

        i_Edges   = std::vector<std::pair<int, int>>(i_NumNodes - 1);
        i_Queries = std::vector<std::pair<int, int>>(i_NumQueries);

        for (int i = 0; i < i_NumNodes - 1; ++i)
        {
            std::cin >> i_Edges[i].first >> i_Edges[i].second;
        }

        for (int i = 0; i < i_NumQueries; ++i)
        {
            std::cin >> i_Queries[i].first >> i_Queries[i].second;
        }
    }

    void ShowOutput()
    {
        for (int result : o_QueryResults)
        {
            std::cout << result << "\n";
        }
    }

private:
    int i_NumNodes   = 0;
    int i_NumQueries = 0;

    std::vector<std::pair<int, int>> i_Edges;
    std::vector<std::pair<int, int>> i_Queries;

    std::vector<int> o_QueryResults;
};
