
#include <vector>
#include "SudokuCell.h"


// The cells within SudokuSet follow the rules of Sudoku, only the values 1-9 may appear, and each only once.

class SudokuSet {
public:
	SudokuSet();
	SudokuSet(int position);
	virtual ~SudokuSet();

	virtual void addCell(SudokuCellPtr);



private:
	std::vector<SudokuCellPtr> mCells;
	int mPosition;


};