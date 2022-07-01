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

  LatinSquare(const std::size_t i_size) : size(i_size)
  {
    for (std::size_t i = 0; i < size * size; i++)
      latin_square.push_back(0);
  }

  friend std::ostream &operator<<(std::ostream &os, const LatinSquare &square)
  {
    for (std::size_t i = 0; i < square.latin_square.size(); i += square.size)
    {
      os << "| ";
      for (std::size_t j = i; j < i + square.size; j++)
        os << square.latin_square[j] << " ";
      os << "|\n";
    }

    return os;
  }
};

struct LatinSquareBuilder
{
  std::size_t size;

  LatinSquareBuilder(const int n) : size(n) {}

  const std::vector<int> get_base_possible_value() const
  {
    std::vector<int> base_possible_value;

    for (int i = 0; i < size; i++)
      base_possible_value.push_back(i + 1);

    return base_possible_value;
  }

  const PossibleValues get_square_possible_values_base() const
  {
    PossibleValues square_possible_values;

    auto base_possible_value = get_base_possible_value();

    for (std::size_t i = 0; i < size; i++)
      for (std::size_t j = 0; j < size; j++)
        square_possible_values[i * size + j] = base_possible_value;

    return square_possible_values;
  }

  const std::optional<LatinSquare>
  build_latin_square_logic(const std::size_t index,
                           const PossibleValues possible_values,
                           const LatinSquare latin_square) const
  {
    if (index == latin_square.latin_square.size())
      return latin_square;

    if (!possible_values.at(index).size())
      return std::nullopt;

    for (const auto value : possible_values.at(index))
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

      if (const auto result = build_latin_square_logic(
              index + 1, temp_possible_values, temp_latin_square))
        return result;
    }

    return std::nullopt;
  }

  const LatinSquare build_latin_square() const
  {
    const auto possible_values = get_square_possible_values_base();
    const LatinSquare latin_square{size};

    return *build_latin_square_logic(0, possible_values, latin_square);
  }
};

int main()
{
  int n;
  std::cout << "Enter N : ";
  std::cin >> n;

  LatinSquareBuilder latin_square{n};

  const auto result = latin_square.build_latin_square();

  std::cout << "Latin Square with size " << n << " : \n" << result;

  return 0;
}