#include <iostream>
#include <vector>
using namespace std;

// Function to print the Sudoku
void printSudoku(const vector<vector<int>>& sudoku) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            cout << sudoku[row][col] << " ";
        }
        cout << endl;
    }
}

// Function to check if placing num at sudoku[row][col] is valid
bool isValid(const vector<vector<int>>& sudoku, int row, int col, int num) 
{
    
    for (int i = 0; i < 9; i++) {
        // Check row and column
        if (sudoku[row][i] == num || sudoku[i][col] == num) {
            return false;
        }
        // Check for 3*3 Grid
        if(sudoku[3*(row/3) + i/3][3*(col/3) + i%3] == num)
            return false;
    } 

    return true;
}

// Backtracking function to solve the Sudoku puzzle
bool solveSudoku(vector<vector<int>>& sudoku) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            // Find an empty cell
            if (sudoku[row][col] == 0) {
                // Try placing numbers in the range of 1-9
                for (int num = 1; num <= 9; num++) {
                    if (isValid(sudoku, row, col, num)) {
                        sudoku[row][col] = num;  // Place this number

                        // Recursively attempt to solve with this placement
                        if (solveSudoku(sudoku)) {
                            return true;
                        }

                        sudoku[row][col] = 0;  // Backtrack!
                    }
                }
                return false;  // No valid number found, so return false
            }
        }
    }
    return true;  // if the Puzzle is solved, return true
}

int main() {
    vector<vector<int>> sudoku(9, vector<int>(9,0));
    // Taking input of the sudoku puzzle from the user
    cout << "Enter the Sudoku puzzle (0 for empty cells):" << endl;
    cout<<"   ";
    for(int i=0;i<9;i++)
    {
        cout<<i+1<<" ";
    }
    cout<<endl;
    for (int i = 0; i < 9; ++i) {
        cout<<i+1<<". ";
        for (int j = 0; j < 9; ++j) {
            cin >> sudoku[i][j];
        }
        cout<<endl;
    }
    // If it's solved print the sudoku otherwise print that it's not possible to solve!
    if (solveSudoku(sudoku)) {
        cout << "\nSolved Sudoku:" << endl;
        printSudoku(sudoku);
    } else {
        cout << "\nSorry but, No solution exists for the provided Sudoku puzzle." << endl;
    }

    return 0;
}