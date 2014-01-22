#ifndef SUDOKUCELL_HEADER
#define SUDOKUCELL_HEADER

#include <memory>
#include <string>

enum SudokuNumber { NONUM = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };


// Use co-prime numbers to determine what a cell is.
namespace SudokuCoPrime {
	enum SudokuCoPrime { ONE = 11, TWO = 17, THREE = 13, FOUR = 19, FIVE = 5,
		SIX = 6, SEVEN = 7, EIGHT = 23, NINE = 9, ALLPRODUCT = 2007835830 };
};



class SudokuCell {
public:
	SudokuCell();
	SudokuCell(int value);
	virtual ~SudokuCell();

	std::string print();
	SudokuCoPrime::SudokuCoPrime getCoPrime();
	SudokuNumber getNumber();

	bool isSet();

	void eliminateNumber(SudokuCoPrime::SudokuCoPrime);		// eliminates the co-prime from the possibilities and reduces the number of possibilities
	bool canBe(SudokuNumber);								// returns true if the cell can take on the value of the SudokuNumber passed
	bool checkOnePossibility();								// if there is only one possible value sets the value of the cell and returns true
	void set(SudokuNumber);											// sets the cell to the int given

private:
	SudokuNumber mValue;
	int mProductPossibilities;
	int mNumPossibilities;

};

SudokuNumber SudokuNumberFromInt (int value);
SudokuNumber SudokuNumberFromSudokuCoPrime (SudokuCoPrime::SudokuCoPrime value);
SudokuCoPrime::SudokuCoPrime SudokuCoPrimeFromInt (int value);

typedef std::shared_ptr<SudokuCell> SudokuCellPtr;
SudokuCellPtr makeSudokuCellPtr(int value);

#endif