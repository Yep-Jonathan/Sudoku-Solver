#include "SudokuCell.h"
#include <sstream>

// shared pointer make command:
SudokuCellPtr makeSudokuCellPtr (int value) {
	return std::make_shared<SudokuCell>(value);
}

SudokuCell::SudokuCell() {
	mValue = SudokuNumber::NONUM;
	mProductPossibilities = SudokuCoPrime::ALLPRODUCT;
	mNumPossibilities = 9;
}

SudokuCell::SudokuCell(int value) {
	if (value != 0) {
		mValue = SudokuNumberFromInt (value);
		mProductPossibilities = 0;
		mNumPossibilities = 1;
	} else {
		mValue = SudokuNumber::NONUM;
		mProductPossibilities = SudokuCoPrime::ALLPRODUCT;
		mNumPossibilities = 9;
	}
}

SudokuCell::~SudokuCell() {

}

std::string SudokuCell::print() {
	if (mValue != SudokuNumber::NONUM) {
		std::stringstream ss;
		ss << mValue;
		return ss.str();
	} else {
		return "-";
	}
}


// Private

SudokuNumber SudokuCell::SudokuNumberFromInt (int value) {
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

SudokuCoPrime::SudokuCoPrime SudokuCell::SudokuCoPrimeFromInt (int value) {
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

