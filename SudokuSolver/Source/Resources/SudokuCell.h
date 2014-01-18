#include <memory>


enum SudokuNumber { NONUM = 0, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE };


// Use co-prime numbers to determine what a cell is.
enum SudokuCoPrime { ONE = 11, TWO = 17, THREE = 13, FOUR = 19, FIVE = 5,
	SIX = 6, SEVEN = 7, EIGHT = 23, NINE = 9, ALLPRODUCT = 2007835830 };



class SudokuCell {
public:
	SudokuCell();
	SudokuCell(int value);
	virtual ~SudokuCell();



private:
	SudokuNumber mValue;
	int mProductPossibilities;
	int mNumPossibilities;

	SudokuNumber SudokuNumberFromInt (int value);
	SudokuCoPrime SudokuCoPrimeFromInt (int value);



};

typedef std::shared_ptr<SudokuCell> SudokuCellPtr;
SudokuCellPtr makeSudokuCell(int value);