#ifndef SUDOKUGRID_HEADER
#define SUDOKUGRID_HEADER

#include <string>
#include <fstream>
#include "SudokuRow.h"
#include "SudokuColumn.h"
#include "SudokuBox.h"
#include "SudokuCell.h"

typedef std::shared_ptr<SudokuRow> SudokuRowPtr;
SudokuRowPtr makeSudokuRowPtr(int position);

typedef std::shared_ptr<SudokuColumn> SudokuColumnPtr;
SudokuColumnPtr makeSudokuColumnPtr(int position);

typedef std::shared_ptr<SudokuBox> SudokuBoxPtr;
SudokuBoxPtr makeSudokuBoxPtr(int position);



class SudokuGrid {
public:
	SudokuGrid(std::string inFile);
	~SudokuGrid();

	bool solve();
	void print();


private:

	SudokuRow mRows[9];
	SudokuColumn mColumns[9];
	SudokuBox mBoxes[9];


};

#endif