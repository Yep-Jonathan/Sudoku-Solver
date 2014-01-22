#include "SudokuSet.h"


SudokuSet::SudokuSet() {
	mPosition = 0;
}

SudokuSet::SudokuSet(int position) {
	mPosition = position;
}

SudokuSet::~SudokuSet() {
	
}

void SudokuSet::addCell(SudokuCellPtr cell) {
	mCells.push_back(cell);
}

void SudokuSet::eliminateCoPrime(SudokuCoPrime::SudokuCoPrime value) {
	for (std::vector<SudokuCellPtr>::iterator i = mCells.begin(); i != mCells.end(); ++i) {
		if (!(*i)->isSet()) {
			(*i)->eliminateNumber(value);
		}
	}
}