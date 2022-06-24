def isSafe(square, num, row, col):
    for r in range(row):
        if square[r][col] == num:
            return False
    
    for c in range(col):
        if square[row][c] == num:
            return False

    return True

def solveLatinSquare(square, size, row, col):
    if 
    