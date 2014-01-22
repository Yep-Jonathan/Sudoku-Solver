/*
 * The following program is a Sudoku Solver created by Jonathan Yep.
 * To use the application, run the exe file with the input file given as an argument.
 * The program will solve the grid, and display it on-screen.
 *
 *
 * Sudoku is a numerical puzzle that requires logic and combinatorics to solve.
 * The rules are fairly simple:
 *		- A 9x9 grid must be filled with the numbers from 1-9, each used 9 times
 *		- Each number from 1-9 must appear exactly once in each row, column, and 3x3 sub-grid
 *
 * Given the above constraints, it is possible to solve a grid if you are given sufficient starting numbers.
 * This program uses various methods to solve a given grid, as outlined below.
 *
 * Placement by Elimination:
 *		- If a cell can be determined to be the only possible location for a particular number, that number must occupy that space.
 *
 *
 */



#include <iostream>
#include "Resources\SudokuGrid.h"

using namespace std;

int main (int argc, char * argv[]) {

	if (argc == 2)
	{
		// Create the Sudoku grid from the input file, and solve it
		// Assumes the input file is in the correct format (9x9 numbers delimited by space with unknown values given 0)
		SudokuGrid grid(argv[1]);
		
		cout << "The input grid is:" << endl;
		grid.print();	// print the original grid
		
		if (grid.solve()) 
		{
			cout << "Solved!  The solved grid is:" << endl;
			grid.print();
		}
		else 
		{
			cout << "The grid could not be solved.  Please check that the numbers are input correctly." << endl;
		}

	}
	else 
	{
		cout << "One argument must be provided to specify the input file." << endl;
	}




	return 0;
}