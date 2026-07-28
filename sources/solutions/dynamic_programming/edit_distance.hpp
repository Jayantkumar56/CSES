
#include <iostream>
#include <algorithm>
#include <vector>



class EditDistance {
private:
    int RecursiveImpl(std::string_view w1, std::string_view w2)
    {
        if (w1.size() == 0 && w2.size() == 0)
        {
            return 0;
        }

        if (w1.size() == 0 || w2.size() == 0)
        {
            return w1.size() == 0 ? w2.size() : w1.size();
        }

        if (w1.front() == w2.front())
        {
            return RecursiveImpl(w1.substr(1), w2.substr(1));
        }

        int insertRes  = RecursiveImpl(w1, w2.substr(1));
        int deleteRes  = RecursiveImpl(w1.substr(1), w2);
        int replaceRes = RecursiveImpl(w1.substr(1), w2.substr(1));

        return 1 + std::min({insertRes, deleteRes, replaceRes});
    }

    int IterativeImpl(std::string_view word1, std::string_view word2)
    {
        const int size1 = word1.size();
        const int size2 = word2.size();

        std::vector distances(size1 + 1, std::vector(size2 + 1, 0));

        for (int i = 0; i < size1; ++i)
        {
            distances[i].back() = size1 - i;
        }

        for (int i = 0; i < size2; ++i)
        {
            distances.back()[i] = size2 - i;
        }

        for (int i = size1 - 1; i >= 0; --i)
        {
            for (int j = size2 - 1; j >= 0; --j)
            {
                if (word1[i] == word2[j])
                {
                    distances[i][j] = distances[i + 1][j + 1];
                    continue;
                }

                const int insertRes  = distances[i][j + 1];
                const int deleteRes  = distances[i + 1][j];
                const int replaceRes = distances[i + 1][j + 1];

                distances[i][j] = 1 + std::min({insertRes, deleteRes, replaceRes});
            }
        }

        return distances.front().front();
    }

public:
    void Solve()
    {
        o_MinDistance = IterativeImpl(i_Word1, i_Word2);
    }

    void ProcessInput()
    {
        std::cin >> i_Word1 >> i_Word2;
    }

    void ShowOutput()
    {
        std::cout << o_MinDistance;
    }

private:
    std::string i_Word1;
    std::string i_Word2;

    int o_MinDistance;
};
