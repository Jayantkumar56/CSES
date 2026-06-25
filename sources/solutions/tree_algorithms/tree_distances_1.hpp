
#include <vector>
#include <iostream>



class TreeDistances1 {
private:
    struct NodeResult {
        int FromNode = 0;
        int Distance = 0;
    };

    struct ProcessingStackElement {
        int Node  = 0;
        int Level = 0;
    };

private:
    auto CreateAdjList() const
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
        std::pair<std::vector<ProcessingStackElement>, std::vector<int>> data{
            std::vector<ProcessingStackElement>(),
            std::vector<int>(i_NumNodes)};

        std::vector<ProcessingStackElement>& processingStack = data.first;
        std::vector<int>&                    parents         = data.second;

        // Create processing stack
        {
            std::vector<bool> visited(i_NumNodes, false);

            parents[0] = -1;

            processingStack.reserve(i_NumNodes);
            processingStack.emplace_back(0, 0);

            for (size_t i = 0; i < i_NumNodes; ++i)
            {
                const auto& currNode   = processingStack[i];
                const auto& children   = adjList[currNode.Node];
                visited[currNode.Node] = true;

                for (const int child : children)
                {
                    if (visited[child])
                    {
                        continue;
                    }

                    processingStack.emplace_back(child, currNode.Level + 1);
                    parents[child] = currNode.Node;
                }
            }
        }

        return data;
    }

public:
    void Solve()
    {
        const std::vector<std::vector<int>> adjList = CreateAdjList();
        const auto& [processingStack, parents]      = CreateProcessingStack(adjList);

        std::vector<std::vector<NodeResult>> nodeResults(i_NumNodes);
        std::vector<int>                     maxDistances(i_NumNodes);

        // First traversal to get max distance from children
        {
            for (int i = static_cast<int>(processingStack.size()) - 1; i >= 0; --i)
            {
                const auto& currNode       = processingStack[i];
                const auto& children       = adjList[currNode.Node];
                auto&       currNodeResult = nodeResults[currNode.Node];

                for (const int child : children)
                {
                    if (parents[currNode.Node] == child)
                    {
                        continue;
                    }

                    const int valueFromChild = maxDistances[child] + 1;

                    if (currNodeResult.size() == 0)
                    {
                        currNodeResult.emplace_back(child, valueFromChild);
                    }
                    else
                    {
                        if (currNodeResult.size() == 1)
                        {
                            currNodeResult.emplace_back(child, valueFromChild);
                        }
                        else if (currNodeResult[0].Distance < valueFromChild)
                        {
                            currNodeResult[0].Distance = valueFromChild;
                            currNodeResult[0].FromNode = child;
                        }
                        if (currNodeResult[1].Distance < currNodeResult[0].Distance)
                        {
                            std::swap(currNodeResult[0], currNodeResult[1]);
                        }
                    }
                }

                maxDistances[currNode.Node] =
                    (currNodeResult.size() == 0) ? 0 : currNodeResult.back().Distance;
            }
        }

        // Second traversal to get max distance from parent
        {
            // starting from 1 since root node don't have parent
            for (size_t i = 1; i < processingStack.size(); ++i)
            {
                const auto& currNode      = processingStack[i];
                const int   parentNode    = parents[currNode.Node];
                const auto& parentResults = nodeResults[parentNode];

                bool       gotResultFromParent = false;
                NodeResult resultFromParent(parentNode, 0);

                for (const auto& result : parentResults)
                {
                    if (result.FromNode == currNode.Node)
                    {
                        continue;
                    }

                    gotResultFromParent = true;

                    resultFromParent.Distance =
                        std::max(resultFromParent.Distance, result.Distance + 1);
                }

                if (gotResultFromParent)
                {
                    maxDistances[currNode.Node] =
                        std::max(maxDistances[currNode.Node], resultFromParent.Distance);
                    nodeResults[currNode.Node].push_back(resultFromParent);
                }

                maxDistances[currNode.Node] = std::max(maxDistances[currNode.Node], currNode.Level);
            }

            o_MaxDistances = std::move(maxDistances);
        }
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
        for (int distance : o_MaxDistances)
        {
            std::cout << distance << " ";
        }
    }

private:
    size_t                           i_NumNodes;
    std::vector<std::pair<int, int>> i_Edges;

    std::vector<int> o_MaxDistances;
};

