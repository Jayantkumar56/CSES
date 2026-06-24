
#include <iostream>
#include <vector>



struct NodeResult {
    int Taken    = 0;
    int NotTaken = 0;
};

class TreeMatching {
public:
    void Solve()
    {
        // Create adjacency matrix
        std::vector<std::vector<int>> adjList(i_NumNodes);

        for (const auto& edge : i_Edges)
        {
            adjList[edge.first - 1].push_back(edge.second - 1);
            adjList[edge.second - 1].push_back(edge.first - 1);
        }

        // Arrange nodes in level order
        std::vector<int> levelOrder;
        levelOrder.reserve(i_NumNodes);
        levelOrder.push_back(0);

        std::vector<int> parent(i_NumNodes);


        for (int i = 0; i < i_NumNodes; ++i)
        {
            const int currNode = levelOrder[i];

            for (const int adjNode : adjList[currNode])
            {
                if (adjNode != parent[currNode])
                {
                    levelOrder.push_back(adjNode);
                    parent[adjNode] = currNode;
                }
            }
        }

        // Traverse from the leafs to root
        std::vector<NodeResult> nodeResults(i_NumNodes);

        for (int i = i_NumNodes - 1; i >= 0; --i)
        {
            const int currNode = levelOrder[i];

            int& currTakenResult    = nodeResults[currNode].Taken;
            int& currNotTakenResult = nodeResults[currNode].NotTaken;

            bool takenAllChild = true;

            // Calculation when not taken
            for (const int adjNode : adjList[currNode])
            {
                if (adjNode == parent[currNode])
                {
                    continue;
                }

                if (nodeResults[adjNode].Taken > nodeResults[adjNode].NotTaken)
                {
                    currNotTakenResult += nodeResults[adjNode].Taken;
                }
                else
                {
                    currNotTakenResult += nodeResults[adjNode].NotTaken;
                    takenAllChild       = false;
                }
            }

            // Calculation when taken
            if (!takenAllChild && adjList[currNode].size() > 0)
            {
                currTakenResult = currNotTakenResult + 1;
                continue;
            }

            currTakenResult = currNotTakenResult;

            for (const int adjNode : adjList[currNode])
            {
                if (adjNode == parent[currNode])
                {
                    continue;
                }

                const int currAdjNodeNotTakenResult = currTakenResult - nodeResults[adjNode].Taken +
                                                      nodeResults[adjNode].NotTaken + 1;

                currTakenResult = std::max(currTakenResult, currAdjNodeNotTakenResult);
            }
        }

        o_MaxEdgesInMatching = std::max(nodeResults[0].Taken, nodeResults[0].NotTaken);
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
        std::cout << o_MaxEdgesInMatching << std::endl;
    }

private:
    int                              i_NumNodes;
    std::vector<std::pair<int, int>> i_Edges;

    int o_MaxEdgesInMatching;
};
