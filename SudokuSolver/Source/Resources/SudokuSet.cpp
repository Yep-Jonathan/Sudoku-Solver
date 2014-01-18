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