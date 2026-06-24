
#pragma once


#include <array>
#include <string_view>



using namespace std::string_view_literals;


template <std::size_t N>
using CStringArray = std::array<std::string_view, N>;


template <typename SolutionT>
struct TestData {};
