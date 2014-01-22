#ifndef SUDOKUROW_HEADER
#define SUDOKUROW_HEADER

#include "SudokuSet.h"
#include <string>

class SudokuRow : public SudokuSet {
public:
	SudokuRow();
	SudokuRow(int position);
	virtual ~SudokuRow();

	// Used in the print function of grid
	std::string print();	

private:




};

#endif