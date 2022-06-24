#include <algorithm>
#include <iostream>
#include <map>
#include <optional>
#include <vector>

using LatinSquareType = std::vector<int>;
using PossibleValues = std::map<std::size_t, std::vector<int>>;

struct LatinSquare
{
  std::size_t size;
  LatinSquareType latin_square;

  LatinSquare(std::size_t i_size) : size(i_size)
  {
    for (std::size_t i = 0; i < size * size; i++)
      latin_square.push_back(0);
  }

  void print() const
  {
    for (std::size_t i = 0; i < size * size; i += size)
    {
      std::cout << "| ";
      for (std::size_t j = i; j < i + size; j++)
        std::cout << latin_square[j] << " ";
      std::cout << "|\n";
    }
  }
};

struct LatinSquareBuilder
{
  std::size_t size;
  PossibleValues base_possible_values;

  LatinSquareBuilder(const int n) : size(n)
  {
    std::vector<int> base;
    for (int i = 0; i < size; i++)
      base.push_back(i + 1);

    for (std::size_t i = 0; i < size; i++)
      for (std::size_t j = 0; j < size; j++)
        base_possible_values[i * size + j] = base;
  }

  std::optional<LatinSquare>
  build_latin_square_impl(std::size_t index, PossibleValues possible_values,
                          LatinSquare latin_square)
  {
    if (index == size * size)
      return latin_square;

    if (!possible_values[index].size())
      return std::nullopt;

    for (const auto value : possible_values[index])
    {
      const auto row_number = index / size;
      const auto col_number = index % size;

      auto temp_latin_square = latin_square;
      auto temp_possible_values = possible_values;

      temp_latin_square.latin_square[index] = value;

      const auto remove_value_from_possible_values =
          [&](std::size_t element_index) {
            temp_possible_values[element_index].erase(
                std::remove(temp_possible_values[element_index].begin(),
                            temp_possible_values[element_index].end(), value),
                temp_possible_values[element_index].end());
          };

      for (std::size_t i = row_number * size; i < (row_number + 1) * size; i++)
        remove_value_from_possible_values(i);

      for (std::size_t i = col_number; i < size * size; i += size)
        remove_value_from_possible_values(i);

      if (auto result = build_latin_square_impl(index + 1, temp_possible_values,
                                                temp_latin_square))
        return result;
    }

    return std::nullopt;
  }

  LatinSquare build_latin_square()
  {
    auto possible_values = base_possible_values;
    LatinSquare latin_square(size);
    return *build_latin_square_impl(0, possible_values, latin_square);
  }
};

int main()
{
  int n;
  std::cout << "Enter N : ";
  std::cin >> n;

  LatinSquareBuilder latin_square{n};

  const auto result = latin_square.build_latin_square();

  std::cout << "Latin Square with size " << n << " : \n";
  result.print();

  return 0;
}