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

SudokuCoPrime::SudokuCoPrime SudokuCell::getCoPrime() {
	return SudokuCoPrimeFromInt(mValue);
}

SudokuNumber SudokuCell::getNumber() {
	return mValue;
}

bool SudokuCell::isSet() {
	return (mValue != SudokuNumber::NONUM);
}

bool SudokuCell::canBe(SudokuNumber value) {
	return (!isSet() && mProductPossibilities % SudokuCoPrimeFromInt(value) == 0);
}

void SudokuCell::eliminateNumber(SudokuCoPrime::SudokuCoPrime value) {
	// Check to ensure the number hasn't already been eliminated from the possibilities product
	if (mProductPossibilities % value == 0) {
		mProductPossibilities /= value;
		mNumPossibilities -= 1;
	}
}

bool SudokuCell::checkOnePossibility() {
	if (mNumPossibilities == 1) {
		this->set(SudokuNumberFromSudokuCoPrime(SudokuCoPrimeFromInt(mProductPossibilities)));
		return true;
	} else {
		return false;
	}
}

void SudokuCell::set(SudokuNumber value) {
	mValue = value;
	mProductPossibilities = 0;
	mNumPossibilities = 1;
}

int SudokuCell::getNumPossibilities() const {
	return mNumPossibilities;
}

int SudokuCell::getProductPossibilites() const {
	return mProductPossibilities;
}


// Global

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

SudokuNumber SudokuNumberFromSudokuCoPrime (SudokuCoPrime::SudokuCoPrime value) {
	switch(value) {
	case SudokuCoPrime::ONE:		return SudokuNumber::ONE;		break;
	case SudokuCoPrime::TWO:		return SudokuNumber::TWO;		break;
	case SudokuCoPrime::THREE:		return SudokuNumber::THREE;		break;
	case SudokuCoPrime::FOUR:		return SudokuNumber::FOUR;		break;
	case SudokuCoPrime::FIVE:		return SudokuNumber::FIVE;		break;
	case SudokuCoPrime::SIX:		return SudokuNumber::SIX;		break;
	case SudokuCoPrime::SEVEN:		return SudokuNumber::SEVEN;		break;
	case SudokuCoPrime::EIGHT:		return SudokuNumber::EIGHT;		break;
	case SudokuCoPrime::NINE:		return SudokuNumber::NINE;		break;
	default:	return SudokuNumber::NONUM;		break;
	}
}

SudokuCoPrime::SudokuCoPrime SudokuCoPrimeFromInt (int value) {
	switch(value) {
	case 1:							return SudokuCoPrime::ONE;			break;
	case SudokuCoPrime::ONE:		return SudokuCoPrime::ONE;		break;
	case 2:							return SudokuCoPrime::TWO;			break;
	case SudokuCoPrime::TWO:		return SudokuCoPrime::TWO;		break;
	case 3:							return SudokuCoPrime::THREE;		break;
	case SudokuCoPrime::THREE:		return SudokuCoPrime::THREE;		break;
	case 4:							return SudokuCoPrime::FOUR;			break;
	case SudokuCoPrime::FOUR:		return SudokuCoPrime::FOUR;		break;
	case 5:							return SudokuCoPrime::FIVE;			break;
	case 6:							return SudokuCoPrime::SIX;			break;
	case 7:							return SudokuCoPrime::SEVEN;		break;
	case 8:							return SudokuCoPrime::EIGHT;		break;
	case SudokuCoPrime::EIGHT:		return SudokuCoPrime::EIGHT;		break;
	case 9:							return SudokuCoPrime::NINE;			break;
	default:	return SudokuCoPrime::ALLPRODUCT;	break;
	}
}

// Finds the two co-primes that multiply to Value (SudokuCoPrime namespace)
SudokuCoPrime::SudokuCoPrimePair SudokuCoPrime::findPair(int value) {
	SudokuCoPrimePair ret;
	// large if statement to find which is the correct multiplicity -- can this be improved?
	if ((value % ONE) == 0) { ret.first = ONE; ret.second = ::SudokuCoPrimeFromInt(value / ONE); }
	else if ((value % TWO) == 0) { ret.first = TWO; ret.second = ::SudokuCoPrimeFromInt(value / TWO); }
	else if ((value % THREE) == 0) { ret.first = THREE; ret.second = ::SudokuCoPrimeFromInt(value / THREE); }
	else if ((value % FOUR) == 0) { ret.first = FOUR; ret.second = ::SudokuCoPrimeFromInt(value / FOUR); }
	else if ((value % FIVE) == 0) { ret.first = FIVE; ret.second = ::SudokuCoPrimeFromInt(value / FIVE); }
	else if ((value % SIX) == 0) { ret.first = SIX; ret.second = ::SudokuCoPrimeFromInt(value / SIX); }
	else if ((value % SEVEN) == 0) { ret.first = SEVEN; ret.second = ::SudokuCoPrimeFromInt(value / SEVEN); }
	else if ((value % EIGHT) == 0) { ret.first = EIGHT; ret.second = ::SudokuCoPrimeFromInt(value / EIGHT); }
	else if ((value % NINE) == 0) { ret.first = NINE; ret.second = ::SudokuCoPrimeFromInt(value / NINE); }		// Should never go here
	else { }

	return ret;
}