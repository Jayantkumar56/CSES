
#include <iostream>
#include <vector>



class BookShop {
public:
    void Solve()
    {
        std::vector<int> prevBookResults(i_Budget + 1);
        std::vector<int> currBookResults(i_Budget + 1);

        for (int i = 0; i < i_BookCount; ++i)
        {
            std::swap(prevBookResults, currBookResults);

            for (int currBudget = 1; currBudget <= i_Budget; ++currBudget)
            {
                currBookResults[currBudget] = prevBookResults[currBudget];

                if (currBudget - i_Books[i].first >= 0)
                {
                    currBookResults[currBudget] = std::max(
                        currBookResults[currBudget],
                        i_Books[i].second + prevBookResults[currBudget - i_Books[i].first]);
                }
            }
        }

        o_PurchasedPages = currBookResults.back();
    }

    void ProcessInput()
    {
        std::cin >> i_BookCount >> i_Budget;

        i_Books.resize(i_BookCount);

        for (auto& book : i_Books)
        {
            std::cin >> book.first;
        }

        for (auto& book : i_Books)
        {
            std::cin >> book.second;
        }
    }

    void ShowOutput()
    {
        std::cout << o_PurchasedPages;
    }

private:
    int i_BookCount;
    int i_Budget;

    // price, pages
    std::vector<std::pair<int, int>> i_Books;

    int o_PurchasedPages;
};
