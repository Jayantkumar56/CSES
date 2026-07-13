
#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>



class MinimizingCoins {
public:
    void Solve()
    {
        std::vector<int> coinCounts(i_Sum + 1, std::numeric_limits<int>::max());
        coinCounts[0] = 0;
        std::ranges::sort(i_Coins);

        for (int i = 1; i <= i_Sum; ++i)
        {
            int currCoinCount = std::numeric_limits<int>::max();

            for (const int coin : i_Coins)
            {
                if (i - coin < 0)
                {
                    break;
                }

                currCoinCount = std::min(currCoinCount, coinCounts[i - coin]);
            }

            coinCounts[i] = currCoinCount +
                            static_cast<int>(currCoinCount != std::numeric_limits<int>::max());
        }

        o_RequiredCoinCount = coinCounts[i_Sum] != std::numeric_limits<int>::max()
                                  ? coinCounts[i_Sum]
                                  : -1;
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
        std::cout << o_RequiredCoinCount;
    }

private:
    int              i_Sum;
    int              i_CoinCount;
    std::vector<int> i_Coins;

    int o_RequiredCoinCount;
};
