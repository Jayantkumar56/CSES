
#pragma once


#include <iostream>
#include <vector>
#include <print>



class Subordinates {
public:
    void Solve()
    {
        // Create Adjacency list
        std::vector<std::vector<int>> adjList(i_NumEmployee);

        for (int i = 1; i < i_NumEmployee; ++i)
        {
            adjList[i_DirectBoss[i] - 1].push_back(i);
        }

        // Arrange nodes in level order
        std::vector<int> levelOrder;
        levelOrder.reserve(i_NumEmployee);

        levelOrder.push_back(0);

        for (int i = 0; i < i_NumEmployee; ++i)
        {
            int currNode = levelOrder[i];

            for (int adjNode : adjList[currNode])
            {
                levelOrder.push_back(adjNode);
            }
        }

        // Traverse from the leafs to root (find subordinates)
        o_Subordinates.resize(i_NumEmployee);

        for (int i = i_NumEmployee - 1; i >= 0; --i)
        {
            int currNode             = levelOrder[i];
            o_Subordinates[currNode] = 0;

            for (int adjNode : adjList[currNode])
            {
                o_Subordinates[currNode] += o_Subordinates[adjNode] + 1;
            }
        }
    }

    void ProcessInput()
    {
        std::cin >> i_NumEmployee;
        i_DirectBoss.resize(i_NumEmployee);

        for (int i = 2; i <= i_NumEmployee; ++i)
        {
            std::cin >> i_DirectBoss[i - 1];
        }
    }

    void ShowOutput()
    {
        for (int subordinate : o_Subordinates)
        {
            std::cout << subordinate << " ";
        }
    }

private:
    int              i_NumEmployee;
    std::vector<int> i_DirectBoss;

    std::vector<int> o_Subordinates;
};
