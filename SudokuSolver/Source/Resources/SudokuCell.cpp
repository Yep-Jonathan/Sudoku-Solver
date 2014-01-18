#include "SudokuCell.h"

// shared pointer make command:
SudokuCellPtr makeSudokuCell (int value) {
	return std::make_shared<SudokuCell>(value);
}

SudokuCell::SudokuCell() {
	mValue = SudokuNumber::NONUM;
	mProductPossibilities = SudokuCoPrime::ALLPRODUCT;
	mNumPossibilities = 9;
}

SudokuCell::SudokuCell(int value) {
	mValue = SudokuNumberFromInt (value);
	mProductPossibilities = 0;
	mNumPossibilities = 1;
}

SudokuCell::~SudokuCell() {

}




// Private

SudokuNumber SudokuNumberFromInt (int value) {
	switch(value) {
	case 1:		return SudokuNumber::ONE;		break;
	case 2:		return SudokuNumber::TWO;		break;
	case 3:		return SudokuNumber::THREE;		break;
	case 4:		return SudokuNumber::FOUR;		break;
	case 5:		return SudokuNumber::FIVE;		break;
	case 6:		return SudokuNumber::SIX;		break;
	case 7:		return SudokuNumber::SEVEN;		break;
	case 8:		return SudokuNumber::EIGHT;		break;
	case 9:		return SudokuNumber::NINE;		break;
	default:	return SudokuNumber::NONUM;		break;
	}
}

SudokuCoPrime SudokuCoPrimeFromInt (int value) {
	switch(value) {
	case 1:		return SudokuCoPrime::ONE;			break;
	case 2:		return SudokuCoPrime::TWO;			break;
	case 3:		return SudokuCoPrime::THREE;		break;
	case 4:		return SudokuCoPrime::FOUR;			break;
	case 5:		return SudokuCoPrime::FIVE;			break;
	case 6:		return SudokuCoPrime::SIX;			break;
	case 7:		return SudokuCoPrime::SEVEN;		break;
	case 8:		return SudokuCoPrime::EIGHT;		break;
	case 9:		return SudokuCoPrime::NINE;			break;
	default:	return SudokuCoPrime::ALLPRODUCT;	break;
	}
}

