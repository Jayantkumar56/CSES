
#include <iostream>
#include <vector>
#include <algorithm>



class CoinCombinations1 {
private:
    static constexpr int mod = 1000'000'000 + 7;

public:
    void Solve()
    {
        std::vector<int> waysCounts(i_Sum + 1);
        waysCounts[0] = 1;
        std::ranges::sort(i_Coins);

        for (int i = 1; i <= i_Sum; ++i)
        {
            for (const int coin : i_Coins)
            {
                if (i - coin < 0)
                {
                    break;
                }

                waysCounts[i] += waysCounts[i - coin];
                waysCounts[i] %= mod;
            }
        }

        o_NumWays = waysCounts[i_Sum];
    }

    void ProcessInput()
    {
        std::cin >> i_CoinCount >> i_Sum;
        i_Coins = std::vector<int>(i_CoinCount);

        for (int i = 0; i < i_CoinCount; ++i)
        {
            std::cin >> i_Coins[i];
        }
    }

    void ShowOutput()
    {
        std::cout << o_NumWays;
    }

private:
    int              i_CoinCount;
    int              i_Sum;
    std::vector<int> i_Coins;

    int o_NumWays;
};
