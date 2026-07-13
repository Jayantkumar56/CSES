
#include <iostream>
#include <vector>
#include <limits>



class RemovingDigits {
private:
    struct DigitItr {
    public:
        constexpr DigitItr(int num) noexcept
            : m_Num(num / 10),
              m_Digit(num % 10)
        {
        }

        constexpr bool HaveDigit() const noexcept
        {
            return m_Num != 0 || m_Digit != 0;
        }

        constexpr int Digit() const noexcept
        {
            return m_Digit;
        }

        constexpr void operator++() noexcept
        {
            m_Digit  = m_Num % 10;
            m_Num   /= 10;
        }

    private:
        int m_Num;
        int m_Digit;
    };

public:
    void Solve()
    {
        std::vector<int> stepCounts(i_N + 1, std::numeric_limits<int>::max());
        stepCounts[0] = 0;

        for (int i = 1; i <= i_N; ++i)
        {
            for (DigitItr digits = i; digits.HaveDigit(); ++digits)
            {
                if (digits.Digit() == 0)
                {
                    continue;
                }

                stepCounts[i] = std::min(stepCounts[i], 1 + stepCounts[i - digits.Digit()]);
            }
        }

        o_MinSteps = stepCounts.back();
    }

    void ProcessInput()
    {
        std::cin >> i_N;
    }

    void ShowOutput()
    {
        std::cout << o_MinSteps;
    }

private:
    int i_N;

    int o_MinSteps;
};
