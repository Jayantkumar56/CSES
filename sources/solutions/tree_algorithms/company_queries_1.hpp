
#include <vector>
#include <iostream>
#include <cstddef>
#include <unordered_map>



class CompanyQueries1 {
private:
    struct Query {
        int QueriedParent;
        int QueryIdx;

        Query(int queriedParent, int queryIdx)
            : QueriedParent(queriedParent),
              QueryIdx(queryIdx)
        {
        }
    };

private:
    std::vector<std::vector<int>> CreateAdjList() const
    {
        std::vector<std::vector<int>> adjList(i_NumEmployee);

        for (size_t i = 1; i < i_DirectBoss.size(); ++i)
        {
            adjList[i_DirectBoss[i] - 1].push_back(i);
        }

        return adjList;
    }

    std::unordered_map<int, std::vector<Query>> GetQueries()
    {
        std::unordered_map<int, std::vector<Query>> queries;

        for (size_t i = 0; i < i_Queries.size(); ++i)
        {
            const auto& currQuery = i_Queries[i];
            queries[currQuery.first - 1].emplace_back(currQuery.second, i);
        }

        return queries;
    }

    // Recursive
    void ResolveQueryForNode(const int                                          currNode,
                             const std::vector<std::vector<int>>&               adjList,
                             std::vector<int>&                                  parentStack,
                             const std::unordered_map<int, std::vector<Query>>& queries,
                             std::vector<int>&                                  queryResult) const
    {
        // Resolve (if any) queries for current node
        if (queries.contains(currNode))
        {
            const std::vector<Query>& currQueries = queries.at(currNode);

            for (const auto& query : currQueries)
            {
                const int parentIdx = static_cast<int>(parentStack.size()) - query.QueriedParent;

                queryResult[query.QueryIdx] = parentIdx < 0 ? -1 : parentStack[parentIdx] + 1;
            }
        }

        // Call on child
        {
            parentStack.push_back(currNode);

            const std::vector<int>& children = adjList[currNode];

            for (const int child : children)
            {
                ResolveQueryForNode(child, adjList, parentStack, queries, queryResult);
            }

            parentStack.pop_back();
        }
    }

    // Iterative
    std::vector<int> ResolveQueries(
        const std::vector<std::vector<int>>&               adjList,
        const std::unordered_map<int, std::vector<Query>>& queries) const
    {
        //                 (Node), (currently processing child of Node)
        std::vector<std::pair<int, int>> processingStack;
        std::vector<int>                 queryResults(i_NumQueries);

        processingStack.reserve(i_NumEmployee);

        {
            const int childIdxToProcess = adjList[0].empty() ? -1 : adjList[0].size() - 1;
            processingStack.emplace_back(0, childIdxToProcess);
        }

        while (!processingStack.empty())
        {
            auto& [currNode, childIdxToProcess] = processingStack.back();

            if (childIdxToProcess == -1)
            {
                processingStack.pop_back();

                // Resolve (if any) queries for current node
                if (queries.contains(currNode))
                {
                    const std::vector<Query>& currQueries = queries.at(currNode);

                    for (const auto& query : currQueries)
                    {
                        const int parentIdx =
                            static_cast<int>(processingStack.size()) - query.QueriedParent;

                        queryResults[query.QueryIdx] =
                            parentIdx < 0 ? -1 : processingStack[parentIdx].first + 1;
                    }
                }

                continue;
            }

            const auto& currChild = adjList[currNode][childIdxToProcess];
            --childIdxToProcess;

            const int childIdxOfChildToProcess =
                adjList[currChild].empty() ? -1 : adjList[currChild].size() - 1;

            processingStack.emplace_back(currChild, childIdxOfChildToProcess);
        }

        return queryResults;
    }

public:
    void Solve()
    {
        const std::vector<std::vector<int>>               adjList = CreateAdjList();
        const std::unordered_map<int, std::vector<Query>> queries = GetQueries();

        o_QueryResults = ResolveQueries(adjList, queries);
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
