
#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>
#include <set>
#include <queue>



class CompanyQueries2 {
private:
    static constexpr int c_BinaryLiftingDimension = []() {
        int numNodes = 200'000;

        auto shifts = std::views::iota(0) | std::views::take_while([numNodes](int i) {
                          return (numNodes >> i) > 0;
                      });

        return 1 + std::ranges::distance(shifts);
    }();

private:
    std::vector<std::vector<int>> GetBinaryLifting() const
    {
        auto parents = std::vector(i_NumEmployee, std::vector(c_BinaryLiftingDimension, -1));

        for (int i = 1; i < i_NumEmployee; ++i)
        {
            parents[i][0] = i_DirectBoss[i] - 1;
        }

        for (int j = 1; j < c_BinaryLiftingDimension; ++j)
        {
            bool modified = false;

            for (int i = 1; i < i_NumEmployee; ++i)
            {
                const int jminusOneParent = parents[i][j - 1];

                if (jminusOneParent == -1)
                {
                    continue;
                }

                modified      = true;
                parents[i][j] = parents[jminusOneParent][j - 1];
            }

            if (!modified)
            {
                break;
            }
        }

        return parents;
    }

    std::vector<std::vector<int>> CreateAdjList() const
    {
        std::vector<std::vector<int>> adjList(i_NumEmployee);

        for (int i = 1; i < i_NumEmployee; ++i)
        {
            adjList[i_DirectBoss[i] - 1].push_back(i);
        }

        return adjList;
    }

    std::vector<int> GetNodeDepths() const
    {
        const auto       adjList = CreateAdjList();
        std::vector<int> depths(i_NumEmployee);
        std::queue<int>  processingQueue;
        std::set<int>    visitedNodes;

        processingQueue.push(0);
        visitedNodes.insert(0);
        int currentDepth = 0;

        while (!processingQueue.empty())
        {
            const int currSize = processingQueue.size();

            for (int i = 0; i < currSize; ++i)
            {
                const int currNode = processingQueue.front();
                processingQueue.pop();

                depths[currNode] = currentDepth;

                for (const int child : adjList[currNode])
                {
                    if (visitedNodes.contains(child))
                    {
                        continue;
                    }

                    processingQueue.push(child);
                    visitedNodes.insert(child);
                }
            }

            ++currentDepth;
        }

        return depths;
    }

    int LiftNode(int node, int levelsToLift, const std::vector<std::vector<int>>& binaryLifting)
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

public:
    void Solve()
    {
        const auto parents = GetBinaryLifting();
        const auto depths  = GetNodeDepths();

        auto queryResultFn = [&](const std::pair<int, int>& nodePair) -> int {
            auto [nodeA, nodeB] = nodePair;
            --nodeA;
            --nodeB;

            if (depths[nodeA] != depths[nodeB])
            {
                const int higherDepthNode = depths[nodeA] > depths[nodeB] ? nodeA : nodeB;
                const int lowerDepthNode  = depths[nodeA] < depths[nodeB] ? nodeA : nodeB;

                const int depthDifference = depths[higherDepthNode] - depths[lowerDepthNode];
                const int liftedNode      = LiftNode(higherDepthNode, depthDifference, parents);

                nodeA = liftedNode;
                nodeB = lowerDepthNode;
            }

            if (nodeA == nodeB)
            {
                return nodeA + 1;
            }

            while (parents[nodeA][0] != parents[nodeB][0])
            {
                int idx = 0;

                while (idx < c_BinaryLiftingDimension - 1
                       && parents[nodeA][idx + 1] != parents[nodeB][idx + 1])
                {
                    ++idx;
                }

                nodeA = parents[nodeA][idx];
                nodeB = parents[nodeB][idx];
            }

            return parents[nodeA][0] + 1;
        };

        auto resultRange = i_Queries | std::views::transform(queryResultFn);
        o_QueryResults   = std::vector(i_NumQueries, 0);

        std::ranges::copy(resultRange.begin(), resultRange.end(), o_QueryResults.begin());
    }

    void ProcessInput()
    {
        std::cin >> i_NumEmployee >> i_NumQueries;

        i_DirectBoss = std::vector<int>(i_NumEmployee, -1);
        i_Queries    = std::vector<std::pair<int, int>>(i_NumQueries);

        for (int i = 1; i < i_NumEmployee; ++i)
        {
            std::cin >> i_DirectBoss[i];
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
    int i_NumEmployee = 0;
    int i_NumQueries  = 0;

    std::vector<int>                 i_DirectBoss;
    std::vector<std::pair<int, int>> i_Queries;

    std::vector<int> o_QueryResults;
};
