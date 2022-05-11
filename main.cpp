#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

class Sudoku {
    private:
        // a fixed 9x9 grid
        std::vector<std::vector<int>> grid;
    public:
        // constructor
        Sudoku(){// empty sudoku
            for (int i(0); i < 9; i++)
                grid.push_back({0,0,0,0,0,0,0,0,0});
        }
        bool checkRowforDigit(int row, int digit){
            for (int i(0); i < 9; i++)
                if(grid.at(row).at(i) == digit)
                    return true;
            return false;
        }
        bool checkColforDigit(int col, int digit){
            for (int i(0); i < 9; i++)
                if(grid.at(i).at(col) == digit)
                    return true;
            return false;
        }
        bool checkBoxforDigit(int x, int y, int digit){
            int boxRow(x - x % 3);
            int boxCol(y - y % 3);

            for (int i(0); i < 3; i++)
                for (int j(0); j < 3; j++)
                    if(grid.at(i + boxRow).at(j + boxCol) == digit)
                        return true;
            return false;
        }

        std::vector<std::vector<int>> getGrid() { return grid; }
        int get(int i, int j) { return grid.at(i).at(j); }
        void set(int i, int j, const int &value){
            // checking the index
            if(i > 8 || i < 0 || j > 8 || j < 0)
                throw std::range_error("Index out of bounds");
            // checking the value
            if(value > 9 || value < 1)
                throw std::logic_error("Ivalid digit");
            // check if cell is taken
            if(grid.at(i).at(j) != 0)
                throw std::logic_error("Cell is taken");
            // check if its already in the row
            if(checkRowforDigit(i, value))
                throw std::logic_error("Already in the row");
            // check if it's already in the column
            if(checkColforDigit(j,value))
                throw std::logic_error("Already in the column");
            // check if it's already in the box
            if(checkBoxforDigit(i,j,value))
                throw std::logic_error("Already in the box");
            // setting the value
            grid.at(i).at(j) = value;
        }

        bool containsEmptyCells(){
            for (int i(0); i < 9; i++){
                if(std::count(grid.at(i).begin(), grid.at(i).end(), 0) != 0)
                    return true;
            }
            return false;
        }
        void findEmptyCell(int &row, int &col){
            for (int i(0); i < 9; i++)
                for (int j(0); j < 9; j++)
                    if(grid.at(i).at(j) == 0){
                        row = i;
                        col = j;
                        return;
                    }
        }
        bool validCell(int x, int y, int digit){
            return !checkBoxforDigit(x, y, digit) && !checkColforDigit(y, digit) && !checkRowforDigit(x, digit);
        }
        // if true its solved if false it calls itself recursively
        bool solve(){
            if(!containsEmptyCells())
                return true;
            // if it contains an empty cell then find it
            int row, col;
            findEmptyCell(row, col);
            for (int i(1); i <= 9; i++){
                if(validCell(row, col, i)){
                    grid.at(row).at(col) = i;
                    if(solve())
                        return true;
                    grid.at(row).at(col) = 0;
                }
            }
        }
        void show() {
            for (int i(0); i < 9; i++){
                if(i == 0 || i == 3 || i == 6)
                    std::cout << "- - - - - - - - - - - - -" << std::endl;
                for (int j(0); j < 9; j++){
                    if(j == 0 || j == 3 || j == 6)
                        std::cout << "| ";
                    std::cout << grid.at(i).at(j) << " ";
                    if(j == 8) std::cout << "|";
                }
                std::cout << std::endl;    
            }
            std::cout << "- - - - - - - - - - - - -";
        }
};

int main(){
    // initial empty sudoku
    Sudoku sudoku;
    // sudoku input
    std::cout << "Insert the number of sudoku digits (17 is minumum): ";
    int n;
    do{
        std::cin >> n;
        if(n < 17)
            std::cout << "It's smaller than 17, please enter again: ";
    } while (n < 17);

    for (int i(0); i < n; i++){
        std::cout << "Inesrt the position (row, column): ";
        int x, y;
        std::cin >> x >> y;
        std::cout << "Inesrt the digit: ";
        int digit;
        std::cin >> digit;
        try {
            sudoku.set(x, y, digit);
        } catch (const std::exception& e) {
            std::cout << e.what() << '\n';
        }
    }
    if(sudoku.solve())
        sudoku.show();
    else std::cout << "No solution :(";
    return 0;
}