#ifndef SUDOKUGRID_HEADER
#define SUDOKUGRID_HEADER

#include <string>
#include <fstream>
#include "SudokuRow.h"
#include "SudokuColumn.h"
#include "SudokuBox.h"
#include "SudokuCell.h"



class SudokuGrid {
public:
	SudokuGrid(std::string inFile);
	~SudokuGrid();

	bool solve();
	void print();


private:
	bool isSolved();
	
	void setProductPossibilities();		// Iterates through the grid and eliminates product possibilities
	bool setByOnePossibility();

	SudokuRow mRows[9];
	SudokuColumn mColumns[9];
	SudokuBox mBoxes[9];


};

#endif