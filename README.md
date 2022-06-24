<!-- Sina Rostami 9822143 -->

# Latin Square Problem Solution (using CSP)

This project will solve latin square problem treating like a Constraint Satisfication Problem and using backtracing algoritm.

## Build and Test

Having proper c++ compliler (std >= `c++17`), you can compile and run this project using these commands:

```bash
g++ latin_square.cc -o latin_square
./latin_square
```

## Documentation

To simplify the complexity of the code some user defined types were created:

1. `LatinSquare` : Contains a latin square data including its size and its cells value (a matrix).
   - In instance creation of this type, It will put `0` in all matrix elements, To indicate that it is a non-invalid value for the element.
   - It is also containts a helper function to simplify priniting the square in the terminal output.
2. `LatinSquareBuilder` : Classifies functions and data structures to create a `latin squre` with size `N`.
   - `std::vector<int> get_base_possible_value()` : This function retruns a base possible value for the given size, as a vector of integers. (e.g : for `N = 3` it will return `{1, 2, 3}`)
   - `PossibleValues get_square_possible_values_base()` : This function returns a base mapping from indices of matrix to theirs possible values. (e.g: for `N = 3` it will return `{0 : {1, 2, 3}, 1 : {1, 2, 3}, ..., 8 : {1, 2, 3}}`)
   - `LatinSquare build_latin_square()` : This function will initiate values for starting algorithm including base possible values and a base empty latin square and call `build_latin_square_logic` function.
   - `std::optional<LatinSquare> build_latin_square_logic(std::size_t index, PossibleValues possible_values, LatinSquare latin_square)` : This function is the main part of the projcet. It is a recursive function with following components:
      - Base Case : If current processing index equals to the size of the matrix, means that latin square is ready, so return it.
      - Recursion Step : If set of possible values for the current processing element is empty, so no solutions can be obtained in this branch, so return a `std::nullopt` (means no solution obtained). otherwise loop over all possible values that can be placed in this element of matrix, put it there, update possible values (delete from possible values of other elements which have common row or column with the current element), and call the function on the next index. If any of the function calls returned a proper result (a latin square), return the first one of them and stop checking other solutions.
3. `main` : this function takes input `N` from the user in standard input and runs the algorithm on it. finally it prints the result of the algorithm on the standard output.
