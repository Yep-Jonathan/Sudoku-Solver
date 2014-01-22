#include "SudokuRow.h"

SudokuRow::SudokuRow() {

}

SudokuRow::SudokuRow(int position) : SudokuSet(position) {

}

SudokuRow::~SudokuRow() {

}

std::string SudokuRow::print() {
	std::string ret;
	int counter = 0;
	for (std::vector<SudokuCellPtr>::iterator i = mCells.begin(); i != mCells.end(); ++i) {
		if (counter == 0) {
			ret = (*i)->print();
		} else if (counter % 3 == 0) {
			ret += "|" + (*i)->print();
		} else {
			ret += " " + (*i)->print();
		}
		++counter;
	}
	return ret;
}