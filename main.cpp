#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <array>

#define DIM 9
#define BLANK 0
#define SPACE " "
#define LINE "|"
#define NEW_ROW "-------------------------------------"
#define GRID_FULL std::make_pair(9,9)

using namespace std;


//Printing the sudoku grid
void print_grid(int grid[DIM][DIM])
{
   ofstream mySudoku;
    mySudoku.open("C:/Users/julia/Downloads/crotes/sudoku_solver/grid_sudoku.txt", ios::app);
//    mySudoku.open("C:./grid_sudoku.txt", ios::app);
   //If the file is not open, then get out
  if (!mySudoku.is_open())
   {
      exit(0);
   }
    for (int i=0; i<DIM; i++)
    {
        mySudoku<< SPACE << SPACE << SPACE << SPACE << endl;
        mySudoku<< NEW_ROW<< endl;

        for (int j=0; j<DIM; j++)
        {
            mySudoku<< SPACE;
            if (BLANK == grid[i][j]) mySudoku<<SPACE;
            else mySudoku<<grid[i][j];
            mySudoku<< SPACE;
            mySudoku<< LINE;
        }
    }
    mySudoku << endl << NEW_ROW << endl << endl;
}

//Function that sees if the number indicated exists in an indicated row
//Then you'll have to indicate the number and the row when calling the function
//If the number corresponds with any number at the row, it will return true; otherwise, false
bool verify_row(int grid[DIM][DIM], int row, int num)
{
    for (int col=0; col<DIM; col++)
        if (grid[row][col] == num)
        {
            return true;
         }
    return false;

}

//Function that sees if the number indicated exists in a given column
//Then you'll have to provide the number and the column (col) when calling the function
//If the number correspond with any number at the column, it will return true; otherwise, false
bool verify_col(int grid[DIM][DIM], int col, int num)
{
    for (int row=0; row<DIM; row++)
        if (grid[row][col] == num) return true;
        return false;

}
//Function that sees if the number indicated exists in an indicated box
//Then you'll have to indicate the column and row that the box iniciates and the number,
//when calling the function.
//If the number corresponds with any number at the box, it will return true, otherwise false
bool verify_box(int grid[DIM][DIM], int box_start_row, int box_start_col, int num)
{
    for (int row = 0; row < 3; row ++)
        for (int col = 0; col < 3; col ++)
            if (grid [row + box_start_row][col + box_start_col] == num) return true;
            return false;
}

//Function that verifies if a certain number can be used
//It will verify if the number doesn't exist in a certain row, column or box
bool num_ok (int grid[DIM][DIM], int row, int col, int num)
{
    return !verify_row(grid, row, num) &&
           !verify_col(grid, col, num) &&
           !verify_box(grid, row - row%3, col - col%3, num);
}

//Take the row and col that have a blank space
pair<int, int> get_unassigned_location(int grid[DIM][DIM])
{
    for (int row=0; row < DIM; row++){
        for(int col = 0; col < DIM; col++){
            if (grid[row][col] ==  BLANK)
            {
                return make_pair(row,col);
            }
        }
    }
    return GRID_FULL;
}

bool solve_sudoku(int grid[DIM][DIM])
{
    //If the Sudoku grid has been filled, we are done
    if (GRID_FULL == get_unassigned_location(grid)) return true;

    //Get an unassigned Sudoku grid location
    pair <int, int> row_and_col = get_unassigned_location(grid);
    int row = row_and_col.first;
    int col = row_and_col.second;

    for(int num = 1; num <= 9; num++)
    {
        //If placing the current number in the unassigned location is valid
        if(num_ok(grid, row, col, num))
        {
            //Make tentative assignment
            grid[row][col] = num;

            //do the same thing again recursively.
            //If after all return true, that means we have fully
            //solved it.
            if(solve_sudoku(grid)) return true;

            // As we were not able to validly go through all
            // of the recursions, we must have an invalid number
            // placement somewhere. Lets go back and try a
            // different number for this particular unassigned location
            grid[row][col] = BLANK;
        }
    }
    // If we have gone through all possible numbers for the current unassigned
    // location, then we probably assigned a bad number early. Lets backtrack
    // and try a different number for the previous unassigned locations.
    return false;
}

int main()
{
    cout << "********************************\n\n\tSudoku Solver\n\n********************************" << endl << endl;
    int grid[DIM][DIM];

    ifstream mySudoku;
   mySudoku.open("C:/Users/julia/Downloads/crotes/sudoku_solver/grid_sudoku.txt");
//       mySudoku.open("grid_sudoku.txt");

   //If the file is not open, then get out
  if (!mySudoku.is_open())
   {
      exit(0);
   }

    //Take the matriz from a file and then put at grid
    for (int i=0; i<DIM; i++)
    {
        for(int j=0; j<DIM; j++)
        {
            mySudoku >> grid[i][j];
        }
    }
 /*       int grid[DIM][DIM] = { { 0, 9, 0, 0, 0, 0, 8, 5, 3 },
                               { 0, 0, 0, 8, 0, 0, 0, 0, 4 },
                               { 0, 0, 8, 2, 0, 3, 0, 6, 9 },
                               { 5, 7, 4, 0, 0, 2, 0, 0, 0 },
                               { 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                               { 0, 0, 0, 9, 0, 0, 6, 3, 7 },
                               { 9, 4, 0, 1, 0, 8, 5, 0, 0 },
                               { 7, 0, 0, 0, 0, 6, 0, 0, 0 },
                               { 6, 8, 2, 0, 0, 0, 0, 9, 0 } };
*/
       print_grid(grid);

       if (true == solve_sudoku(grid))
        {
           print_grid(grid);

       }
        else
        {
            cout << "No solution exists for the given Sudoku" << endl << endl;
        }
      mySudoku.close();
    return 0;
}
