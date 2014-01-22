#include "SudokuGrid.h"
#include <iostream>

SudokuGrid::SudokuGrid(std::string inFile) {
	
	// Initialize the Rows and Columns
	for (int i = 0; i < 9; ++i) {
		mRows[i] = SudokuRow(i);
		mColumns[i] = SudokuColumn(i);
		mBoxes[i] = SudokuBox(i);
	}

	// Read values from inFile and store them in the correct locations
	std::ifstream input;
	input.open(inFile);
	SudokuCellPtr cell;
	int cellValue;

	// Constant time for loop
	for (int row = 0; row < 9; ++row) {
		for (int column = 0; column < 9; ++column) {

			// Read the next cell value
			if (!(input >> cellValue)) {
				std::cout << "Inputting failed, please check your input file" << std::endl;
			}

			// Make the cell, and add it to the appropriate structure
			cell = makeSudokuCellPtr(cellValue);
			mRows[row].addCell(cell);
			mColumns[column].addCell(cell);
			mBoxes[3*(row/3) + (column/3)].addCell(cell);
		}
	}

}

SudokuGrid::~SudokuGrid() {

}

bool SudokuGrid::solve() {
	int count = 0;

	while (!isSolved()) {
		setProductPossibilities();
		
		// Will perform one or more of the following solving algorithms (basic -> more advanced)
		if (setByOnePossibility()) { }
		else if (setByOnlyOnePossibilityInSet()) { }
		else if (eliminateByBoxes()) { }

		++count;
		// At least one value should be set each iteration
		if (count > 200) {
			print();
			return false;
		}
	}
	
	return true;
}


void SudokuGrid::print() {
	for (int row = 0; row < 9; ++row) {
		if (row % 3 == 0) {
			std::cout << "-------------------" << std::endl;
		}
		std::cout << "|" << mRows[row].print() << "|" << std::endl;
	}
	std::cout << "-------------------" << std::endl;
}



// Private Functions
bool SudokuGrid::isSolved() {
	int countSolved = 0;

	// Count the number of solved cells (TODO: checking if the solution is correct)
	for (int row = 0; row < 9; ++row) {
		for (std::vector<SudokuCellPtr>::iterator i = mRows[row].mCells.begin(); i != mRows[row].mCells.end(); ++i) {
			if ((*i)->isSet()) { ++countSolved; } 
		}
	}
	return (countSolved == 81);
}


void SudokuGrid::setProductPossibilities() {

	// Iterate through the row vectors, and call eliminate on the corresponding row/column/box if a value exists in the cell
	for (int row = 0; row < 9; ++row) {
		for (std::vector<SudokuCellPtr>::iterator i = mRows[row].mCells.begin(); i != mRows[row].mCells.end(); ++i) {
			if ((*i)->getNumber() != SudokuNumber::NONUM) {
				mRows[row].eliminateCoPrime((*i)->getCoPrime());
				mColumns[i - mRows[row].mCells.begin()].eliminateCoPrime((*i)->getCoPrime());
				mBoxes[3*(row/3) + ((i - mRows[row].mCells.begin())/3)].eliminateCoPrime((*i)->getCoPrime());
			}
		}	
	}
}

bool SudokuGrid::setByOnePossibility() {
	bool setAtLeastOneValue = false;

	// Iterate through the row vectors, and check if only one possibility exists for values that have not been set yet.  If a value has been set, call eliminate on the corresponding row/column/box.
	for (int row = 0; row < 9; ++row) {
		for (std::vector<SudokuCellPtr>::iterator i = mRows[row].mCells.begin(); i != mRows[row].mCells.end(); ++i) {
			if (!(*i)->isSet() && (*i)->checkOnePossibility()) {
				mRows[row].eliminateCoPrime((*i)->getCoPrime());
				mColumns[i - mRows[row].mCells.begin()].eliminateCoPrime((*i)->getCoPrime());
				mBoxes[3*(row/3) + ((i - mRows[row].mCells.begin())/3)].eliminateCoPrime((*i)->getCoPrime());
				setAtLeastOneValue = true;
			}
		}	
	}
	
	return setAtLeastOneValue;
}

bool SudokuGrid::setByOnlyOnePossibilityInSet() {
	bool setAtLeastOneValue = false;

	// Iterate through all the row vectors, then column, then boxes to see if any values can be set
	for (int i = 0; i < 9; ++i) {
		setAtLeastOneValue = (mRows[i].setByOnePossibility() || setAtLeastOneValue);
		setAtLeastOneValue = (mColumns[i].setByOnePossibility() || setAtLeastOneValue);
		setAtLeastOneValue = (mBoxes[i].setByOnePossibility() || setAtLeastOneValue);
	}

	return setAtLeastOneValue;

}

bool SudokuGrid::eliminateByBoxes() {
	bool eliminateAtLeastOneValue = false;
	SudokuNumber numToLookFor;
	bool hasNumber;
	int possiblePlaces = 0;
	int loc1 = -1, loc2 = -1, loc3 = -1;


	for (int box = 0; box < 9; ++box) {
		for (int j = 1; j < 10; ++j) {
			numToLookFor = SudokuNumberFromInt(j);
			hasNumber = false;
			possiblePlaces = 0;
			loc1 = -1; loc2 = -1, loc3 = -1;

			// Check each box if there is only two/three locations for a value.  If so, check if these are aligned in a row/column and if so eliminate them from the row/column
			for (std::vector<SudokuCellPtr>::iterator i = mBoxes[box].mCells.begin(); i != mBoxes[box].mCells.end(); ++i) {
				if ((*i)->isSet() && (*i)->getNumber() == numToLookFor) {
					hasNumber = true;
				}
				
				if (!(*i)->isSet() && (*i)->canBe(numToLookFor)) {
					possiblePlaces += 1;
					if (loc1 == -1) {
						loc1 = (i - mBoxes[box].mCells.begin());
					} else if (loc2 == -1) {
						loc2 = (i - mBoxes[box].mCells.begin());
					} else if (loc3 == -1) {
						loc3 = (i - mBoxes[box].mCells.begin());
					}
				}
			}
			
			if (!hasNumber && possiblePlaces == 2) {
				// we know loc1 must be less than loc2
				// Check if they are in the same column, and eliminate the number from that column if so
				if (loc1 % 3 == loc2 % 3) {
					mColumns[(box % 3)*3 + (loc1 % 3)].eliminateCoPrimeWithSkip(SudokuCoPrimeFromInt(numToLookFor), box / 3);
					eliminateAtLeastOneValue = true;
				} else if ((loc1 / 3) == (loc2 / 3)) {
					mRows[(box / 3)*3 + (loc1 / 3)].eliminateCoPrimeWithSkip(SudokuCoPrimeFromInt(numToLookFor), box % 3);
					eliminateAtLeastOneValue = true;
				}
			}

			if (!hasNumber && possiblePlaces == 3) {
				// we know loc1 < loc2 < loc3
				if (loc1 % 3 == loc2 % 3 && loc1 % 3 == loc3 % 3) {
					mColumns[(box % 3)*3 + (loc1 % 3)].eliminateCoPrimeWithSkip(SudokuCoPrimeFromInt(numToLookFor), box / 3);
					eliminateAtLeastOneValue = true;
				} else if ((loc1 / 3) == (loc2 / 3) && (loc1 / 3) == (loc3 / 3)) {
					mRows[(box / 3)*3 + (loc1 / 3)].eliminateCoPrimeWithSkip(SudokuCoPrimeFromInt(numToLookFor), box % 3);
					eliminateAtLeastOneValue = true;
				}
			}
		}
	}

	return eliminateAtLeastOneValue;
}