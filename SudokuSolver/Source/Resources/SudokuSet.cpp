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

void SudokuSet::eliminateCoPrimeWithSkip(SudokuCoPrime::SudokuCoPrime value, int skip) {
	for (std::vector<SudokuCellPtr>::iterator i = mCells.begin(); i != mCells.end(); ++i) {
		if (!(*i)->isSet() && ((i - mCells.begin())/3) != skip) {
			(*i)->eliminateNumber(value);
		}
	}
}


bool SudokuSet::setByOnePossibility() {
	bool setAtLeastOneValue = false;
	SudokuNumber numToLookFor;
	bool hasNumber = false;
	int possiblePlaces = 0;

	// Note: j starts at 1 here because of the way the enum is set up
	for (int j = 1; j < 10; ++j) {
		// Iterate over mCells to see if the number exists
		numToLookFor = SudokuNumberFromInt(j);
		hasNumber = false;
		possiblePlaces = 0;

		for (std::vector<SudokuCellPtr>::iterator i = mCells.begin(); i != mCells.end(); ++i) {
			if ((*i)->isSet() && (*i)->getNumber() == numToLookFor) {
				hasNumber = true;
				break;
			}
		}

		// If the number is not in the set, try to find a place for it
		if (!hasNumber) {
			for (std::vector<SudokuCellPtr>::iterator i = mCells.begin(); i != mCells.end(); ++i) {
				if (!(*i)->isSet() && (*i)->canBe(numToLookFor)) {
					possiblePlaces += 1;
				}
			}
			// If there is only one possible place, find it and set it
			if (possiblePlaces == 1) {
				for (std::vector<SudokuCellPtr>::iterator i = mCells.begin(); i != mCells.end(); ++i) {
					if ((*i)->canBe(numToLookFor)) {
						(*i)->set(numToLookFor);
						setAtLeastOneValue = true;
						break;
					}
				}
			}
		}
	}

	return setAtLeastOneValue;
}