
#include <iostream>
#include <vector>
#include <unordered_set>
#include <array>



class TreeDiameter {
private:
    struct NodeResult {
        int ChildToChild = 0;
        int ChildToNode  = 0;
        int ParentNode   = 0;
    };

private:
    // Recursive
    NodeResult SolveForNode(std::vector<std::vector<int>>& adjList,
                            int                            currNode,
                            std::unordered_set<int>&       visitedNodes)
    {
        visitedNodes.insert(currNode);

        std::vector<int>&  children = adjList[currNode];
        NodeResult         currentResult;
        std::array<int, 2> maxChildToNode = {0, 0};

        for (int child : children)
        {
            if (visitedNodes.contains(child))
            {
                continue;
            }

            NodeResult childResult = SolveForNode(adjList, child, visitedNodes);

            currentResult.ChildToChild =
                std::max(currentResult.ChildToChild, childResult.ChildToChild);

            maxChildToNode[0] = std::max(maxChildToNode[0], childResult.ChildToNode + 1);

            if (maxChildToNode[0] > maxChildToNode[1])
            {
                std::swap(maxChildToNode[0], maxChildToNode[1]);
            }
        }

        currentResult.ChildToChild =
            std::max(currentResult.ChildToChild, maxChildToNode[0] + maxChildToNode[1]);

        currentResult.ChildToNode = maxChildToNode[1];
        return currentResult;
    }

    // Iterative
    NodeResult SolveForNode(const std::vector<std::vector<int>>& adjList)
    {
        const int nodeCount = adjList.size();

        std::vector<int> processingStack;
        processingStack.reserve(nodeCount);

        std::vector<NodeResult> nodeResults(nodeCount);

        // Fill processing stack in order of nodes
        {
            std::vector<bool> visitedNodes(nodeCount, false);

            visitedNodes[0] = true;
            processingStack.push_back(0);

            for (int currentNodeIdx = 0; currentNodeIdx < nodeCount; ++currentNodeIdx)
            {
                const int   currentNode = processingStack[currentNodeIdx];
                const auto& children    = adjList[currentNode];

                for (const int child : children)
                {
                    if (visitedNodes[child])
                    {
                        continue;
                    }

                    nodeResults[child].ParentNode = currentNode;
                    visitedNodes[child]           = true;
                    processingStack.push_back(child);
                }
            }
        }

        while (!processingStack.empty())
        {
            const int currentNode = processingStack.back();
            processingStack.pop_back();

            const auto&        children       = adjList[currentNode];
            NodeResult&        currentResult  = nodeResults[currentNode];
            std::array<int, 2> maxChildToNode = {0, 0};

            for (const int child : children)
            {
                const NodeResult& childResult = nodeResults[child];

                if (child == currentResult.ParentNode)
                {
                    continue;
                }

                currentResult.ChildToChild =
                    std::max(currentResult.ChildToChild, childResult.ChildToChild);

                maxChildToNode[0] = std::max(maxChildToNode[0], childResult.ChildToNode + 1);

                if (maxChildToNode[0] > maxChildToNode[1])
                {
                    std::swap(maxChildToNode[0], maxChildToNode[1]);
                }
            }

            currentResult.ChildToChild =
                std::max(currentResult.ChildToChild, maxChildToNode[0] + maxChildToNode[1]);

            currentResult.ChildToNode = maxChildToNode[1];
        }

        return nodeResults[0];
    }

public:
    void Solve()
    {
        // Create adjacency list
        std::vector<std::vector<int>> adjList(i_NumNodes);

        for (const auto& edge : i_Edges)
        {
            adjList[edge.first - 1].push_back(edge.second - 1);
            adjList[edge.second - 1].push_back(edge.first - 1);
        }

        std::unordered_set<int> visitedNodes;
        visitedNodes.reserve(i_NumNodes);

        // Starting from node 0 assuming it be root (exact root doesn't matter)
        NodeResult result = SolveForNode(adjList);
        o_TreeDiameter    = std::max(result.ChildToChild, result.ChildToNode);
    }

    void ProcessInput()
    {
        std::cin >> i_NumNodes;
        i_Edges.resize(i_NumNodes - 1);

        for (int i = 0; i < i_NumNodes - 1; ++i)
        {
            std::cin >> i_Edges[i].first >> i_Edges[i].second;
        }
    }

    void ShowOutput()
    {
        std::cout << o_TreeDiameter;
    }

private:
    int                              i_NumNodes;
    std::vector<std::pair<int, int>> i_Edges;

    int o_TreeDiameter;
};
