
#include <iostream>
#include <vector>



class GridPaths1 {
private:
    static constexpr int mod = 1'000'000'000 + 7;

    template <typename T>
    struct Matrix {
        std::vector<T> Data;
        int            Rows;
        int            Cols;

        Matrix() = default;

        Matrix(int rows, int cols, int defaultValue = 0)
            : Data(rows * cols, defaultValue),
              Rows(rows),
              Cols(cols)
        {
        }

        void Resize(int rows, int cols)
        {
            Data.resize(rows * cols);
            Rows = rows;
            Cols = cols;
        }

        T& operator()(int row, int col) noexcept
        {
            return Data[row * Cols + col];
        }

        const T& operator()(int row, int col) const noexcept
        {
            return Data[row * Cols + col];
        }
    };

public:
    void Solve()
    {
        if (m_Grid(i_N - 1, i_N - 1) == '*')
        {
            o_MinSteps = 0;
            return;
        }

        const int endIdx = i_N - 1;

        Matrix<int> numPaths(i_N, i_N);
        numPaths(endIdx, endIdx) = 1;

        for (int i = i_N - 2; i >= 0; --i)
        {
            numPaths(endIdx, i) = (m_Grid(endIdx, i) == '*') ? 0 : numPaths(endIdx, i + 1);
        }

        for (int i = i_N - 2; i >= 0; --i)
        {
            numPaths(i, endIdx) = (m_Grid(i, endIdx) == '*') ? 0 : numPaths(i + 1, endIdx);
        }

        for (int i = i_N - 2; i >= 0; --i)
        {
            for (int j = i_N - 2; j >= 0; --j)
            {
                numPaths(i, j)  = m_Grid(i, j) == '*' ? 0 : numPaths(i + 1, j) + numPaths(i, j + 1);
                numPaths(i, j) %= mod;
            }
        }

        o_MinSteps = numPaths(0, 0);
    }

    void ProcessInput()
    {
        std::cin >> i_N;
        m_Grid.Resize(i_N, i_N);

        for (int i = 0; i < i_N; ++i)
        {
            for (int j = 0; j < i_N; ++j)
            {
                std::cin >> m_Grid(i, j);
            }
        }
    }

    void ShowOutput()
    {
        std::cout << o_MinSteps;
    }

private:
    int          i_N;
    Matrix<char> m_Grid;

    int o_MinSteps;
};
