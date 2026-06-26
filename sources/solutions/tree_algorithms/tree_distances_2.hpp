
#include <vector>
#include <iostream>
#include <cstdint>
#include <utility>



class TreeDistances2 {
private:
    std::vector<std::vector<int>> CreateAdjList() const
    {
        std::vector<std::vector<int>> adjList(i_NumNodes);

        for (const auto& edge : i_Edges)
        {
            adjList[edge.first - 1].push_back(edge.second - 1);
            adjList[edge.second - 1].push_back(edge.first - 1);
        }

        return adjList;
    }

    auto CreateProcessingStack(const std::vector<std::vector<int>>& adjList) const
    {
        auto processingData =
            std::pair<std::vector<int>, std::vector<int>>{std::vector<int>(),
                                                          std::vector<int>(i_NumNodes)};

        std::vector<int>& processingStack = processingData.first;
        std::vector<int>& parents         = processingData.second;
        std::vector<bool> visitedNodes(i_NumNodes, false);

        processingStack.reserve(i_NumNodes);

        processingStack.push_back(0);
        parents[0] = -1;

        for (size_t i = 0; i < i_NumNodes; ++i)
        {
            const int   currNode   = processingStack[i];
            const auto& children   = adjList[currNode];
            visitedNodes[currNode] = true;

            for (const int child : children)
            {
                if (visitedNodes[child])
                {
                    continue;
                }

                processingStack.push_back(child);
                parents[child] = currNode;
            }
        }

        return processingData;
    }

public:
    void Solve()
    {
        const std::vector<std::vector<int>> adjList = CreateAdjList();
        const auto& [processingStack, parents]      = CreateProcessingStack(adjList);

        std::vector<int64_t> decendentsCount(i_NumNodes);
        std::vector<int64_t> distanceSums(i_NumNodes);

        // First pass to get distance sum from children
        {
            for (int i = static_cast<int>(processingStack.size()) - 1; i >= 0; --i)
            {
                const int   currNode = processingStack[i];
                const auto& children = adjList[currNode];

                for (const int child : children)
                {
                    if (parents[currNode] == child)
                    {
                        continue;
                    }

                    distanceSums[currNode]    += distanceSums[child];
                    decendentsCount[currNode] += decendentsCount[child] + 1;
                }

                distanceSums[currNode] += decendentsCount[currNode];
            }
        }

        // Second pass to get distance sum from parent
        {
            for (size_t i = 1; i < processingStack.size(); ++i)
            {
                const int currNode   = processingStack[i];
                const int parentNode = parents[currNode];

                const int64_t parentDistanceContrib =
                    distanceSums[parentNode] - distanceSums[currNode] - decendentsCount[currNode] -
                    static_cast<int64_t>(1);

                const int64_t parentDecendentContrib =
                    static_cast<int64_t>(i_NumNodes - 1) - decendentsCount[currNode];

                distanceSums[currNode] += parentDecendentContrib + parentDistanceContrib;
            }
        }

        o_SumDistances = std::move(distanceSums);
    }

    void ProcessInput()
    {
        std::cin >> i_NumNodes;
        i_Edges = std::vector<std::pair<int, int>>(i_NumNodes - 1);

        for (size_t i = 0; i < i_NumNodes - 1; ++i)
        {
            std::cin >> i_Edges[i].first >> i_Edges[i].second;
        }
    }

    void ShowOutput()
    {
        for (const int64_t sumDistance : o_SumDistances)
        {
            std::cout << sumDistance << " ";
        }
    }

private:
    size_t                           i_NumNodes;
    std::vector<std::pair<int, int>> i_Edges;

    std::vector<int64_t> o_SumDistances;
};
