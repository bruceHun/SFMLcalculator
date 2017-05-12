//Ifndef-define-endif is used to prevent multiple inclusion of the same header file
#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <stack>
#include <sstream>
#include "NumberObject.h"
#include "Integer.h"
#include "Decimal.h"

//What operation are we performing?
enum Operator {
	ADD = '+',
	SUBTRACT = '-',
	MULTIPLY = '*',
	DIVIDE = '/',
	POW = '^',
	NONE = 0xFF
};

//Sign of the inserted number
enum Sign {
	POSITIVE = +1,
	NEGATIVE = -1
};

//Which button did the user click?
enum ButtonCode {
	ZERO = '0',
	ONE = '1',
	TWO = '2',
	THREE = '3',
	FOUR = '4',
	FIVE = '5',
	SIX = '6',
	SEVEN = '7',
	EIGHT = '8',
	NINE = '9',
	SWAP_SIGN,
	INSERT_DOT,
	PLUS = '+',
	MINUS = '-',
	PER = '*',
	SOLIDUS = '/',
	EQUAL = '=',
	CLEAR = 'c',
	FACTORIAL = '!',
	POWER = '^',
	SQRT = 'V',
	FN,
	LEFT_PRN = '(',
	RIGHT_PRN = ')',
	LEFT_SHIFT = '<',
	RIGHT_SHIFT = '>',
	COMPLEX,
	UA = 'A',
	UB = 'B',
	UC ='C'
};

//Define the calculator class
class Calculator {
	//Private means only class methods and few other things can access these elements
private:
	sf::RenderWindow Window; //Window on which we'll render everything
	std::vector<std::pair<sf::RectangleShape, sf::Text>> RegularButtons; //Buttons we'll have to click (numbers, sign swap and dot)
	std::vector <std::pair<sf::RectangleShape, sf::Text>> FnButtons;
	std::vector<std::pair<sf::RectangleShape, sf::Text>> OpButtons; //+, -, *, /
	std::vector<std::pair<sf::RectangleShape, sf::Text>> ExButtons; //=,
	std::pair<sf::RectangleShape, sf::Text> Display; //Calculator display
	sf::Text SignString; //+ - sign

	NumberBase *PrecValue, *Value;
	string A, B, C;
	Integer *intgr;
	Decimal *decml;
	bool DotInserted; //Has . already been inserted in this value?
	bool OpInserted;
	bool FactorialON;
	bool PowerON;
	bool AlgebraON;
	bool FN_ON;
	bool CmplxON;
	bool AlgebraRestrict;
	
	Operator Op; //Which operation do we have to perform?
	size_t InsertedCharacters; //Characters (ciphers or dot) inserted
							   //Internal variables
	std::ostringstream stream;
	Sign sign;
	bool IsFirstAlreadyReplaced;
	bool ResultOutputted;
	int Open_parenthesis;

	//Function used to elaborate button press
	void InsertCharacter(ButtonCode bc); //Press a button
	string lineParser(const string&);

										 //Public members can be freely accessed
public:
	//Class Constructor (Function that is automatically called when you istantiate this class)
	Calculator();
	//Class Destructor (Function that is automatically called when the object goes "out of scope")
	~Calculator();
	//Handle events, display output
	void Start();
};

#endif // CALCULATOR_H
