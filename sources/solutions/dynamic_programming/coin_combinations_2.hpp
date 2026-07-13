
#include <iostream>
#include <vector>



class CoinCombinations2 {
private:
    static constexpr int mod = 1'000'000'000 + 7;

public:
    void Solve()
    {
        std::vector<int> currCoinWays(i_Sum + 1);
        std::vector<int> prevCoinWays(i_Sum + 1);

        currCoinWays[0] = 1;
        prevCoinWays[0] = 1;

        for (int i = 1; i <= i_Sum; ++i)
        {
            if (i - i_Coins[0] >= 0)
            {
                currCoinWays[i] += currCoinWays[i - i_Coins[0]];
                currCoinWays[i] %= mod;
            }
        }

        for (int i = 1; i < i_CoinCount; ++i)
        {
            std::swap(currCoinWays, prevCoinWays);

            for (int j = 1; j <= i_Sum; ++j)
            {
                currCoinWays[j] = prevCoinWays[j];

                if (j - i_Coins[i] >= 0)
                {
                    currCoinWays[j] += currCoinWays[j - i_Coins[i]];
                    currCoinWays[j] %= mod;
                }
            }
        }

        o_NumWays = currCoinWays.back();
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
