#ifndef SUDOKUSET_HEADER
#define SUDOKUSET_HEADER

#include <vector>
#include "SudokuCell.h"


// The cells within SudokuSet follow the rules of Sudoku, only the values 1-9 may appear, and each only once.

class SudokuSet {
public:
	SudokuSet();
	SudokuSet(int position);
	virtual ~SudokuSet();

	virtual void addCell(SudokuCellPtr);

	void eliminateCoPrime(SudokuCoPrime::SudokuCoPrime);						// eliminate the number from the entire set
	void eliminateCoPrimeWithSkip(SudokuCoPrime::SudokuCoPrime, int skip);		// eliminate the number, skipping the corresponding box (0, 1, or 2 wrt the row/column)

	bool setByOnePossibility();

	std::vector<SudokuCellPtr> mCells;

protected:	
	int mPosition;

};

#endif