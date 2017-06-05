//
//  CalculatorOperation.cpp
//  Calculator
//
//  Created by Bruce on 03/06/2017.
//  Copyright © 2017 Bruce. All rights reserved.
//

#include "Calculator.h"

#include <iostream>
#include <sstream> //Needed for std::ostringstream
#include <cmath>
#include <queue>
#include <stdexcept>

void Calculator::InsertCharacter(ButtonCode bc) {
	//Checks which button has been pressed
	switch (bc) {
		//	break;
		case ZERO:
		case ONE:
		case TWO:
		case THREE:
		case FOUR:
		case FIVE:
		case SIX:
		case SEVEN:
		case EIGHT:
		case NINE:
			
		case UA:
		case UB:
		case UC:
			
		case LEFT_PRN:
		case RIGHT_PRN:
			
		case PLUS:
		case MINUS:
		case PER:
		case SOLIDUS:
		{
			if (!ResultOutputted && InsertedCharacters < 300) { // --------- max  length ------------
				
					char strback = '\0';
					if (!stream.str().empty())  strback = stream.str().back();
					bool isDigit(false), isAlgebra(false), isOpratr(false);
					//if (OpInserted && (bc >= PLUS && bc <= SOLIDUS)) break;
					if (bc == PLUS || bc == MINUS || bc == PER || bc == SOLIDUS) {
						if (OpInserted) break;  // prevent concatenation of operators
						isOpratr = true;
					}
					else if (bc >= ZERO	&& bc <= NINE) { isDigit = true; }
					else if (bc >= UA	&& bc <= UC) { isAlgebra = true; }
					
					if (FN_ON && !AlgebraON && isAlgebra)
					{// Algebra defining mode
						stream.str("");
						stream << (char)bc << "= ";
						FN_ON = false;
						AlgebraON = true;
						InsertedCharacters = 3;
						break;
					}
					if (isDigit)
					{/////////////////////// Something needs to be SOLVED!!! ////////////////////////////////
						//if (DigitInserted && !OpInserted && !LeftParenthesis && !PowerON) break;
						if (AlgebraRestrict && !CmplxON && !PowerON) break;
					}
					if (isAlgebra)
					{
						if (!AlgebraRestrict)
						{
							if (!stream.str().empty() && (DigitInserted || RightParenthesis))
								break; // algebra can not follow a ditgit or a factorial
							AlgebraRestrict = true;
						}
						else break;
					}
					
					if (CmplxON) { // Complex mode  is on
						if (bc != PER && bc != SOLIDUS && bc != LEFT_PRN && bc != RIGHT_PRN && !isAlgebra)
						{
							string line = stream.str();
							if	(CmplxParts == REAL)
							{
								line.pop_back(); line.pop_back();
								stream.str("");
								stream << line << (char)bc << "+i";
							}
							else if (CmplxParts == IMAG)
							{
								line.pop_back();
								stream.str("");
								stream << line << (char)bc << "i";
							}
							
						}
						break;
					}
					else if (PowerON) {	// pw function is on
						if (!isOpratr && bc != LEFT_PRN && bc != RIGHT_PRN)
						{
							if (stream.str().substr(stream.str().find("^")).length() > 4) break;
							stream << (char)bc;
							++InsertedCharacters;
						}
						break;
					}
					else if (SqrtON) { // sqrt function is on
						if (bc != PER && bc != SOLIDUS && bc != LEFT_PRN && bc != RIGHT_PRN)
						{
							string line = stream.str();
							line.pop_back(); line.pop_back();
							stream.str("");
							stream << line << (char)bc;
							// if (InsertedCharacters > 0 && InsertedCharacters % 60 == 0) stream << '\n';
							stream << " ]";
							++InsertedCharacters;
							DigitInserted = (isDigit) ? true : false;
						}
						break;
					}
					else if	(FactorialON) { // n! function is on
						if (!isOpratr && bc != LEFT_PRN && bc != RIGHT_PRN)
						{
							// if (InsertedCharacters > 7) break;
							string line = stream.str();
							line.pop_back(); line.pop_back();
							stream.str("");
							stream << line << (char)bc << "]!";
							++InsertedCharacters;
							DigitInserted = (isDigit) ? true : false;
						}
						break;
					}
					
					
					//////////////////////// M A I N   I N S E R T I O N ////////////////////////
				
						if (isOpratr || bc == LEFT_PRN || bc == RIGHT_PRN)
						{
							if (bc == LEFT_PRN && (InsertedCharacters && !OpInserted && !LeftParenthesis && !(AlgebraON && InsertedCharacters == 3))) break;
							if (isOpratr && !InsertedCharacters) break;
							if (InsertedCharacters && (DigitInserted || (strback >= UA && strback <= UC)))
							{ stream << ' '; ++InsertedCharacters; }
							DotInserted = false; // another number, another dot
							AlgebraRestrict = false; // operator inserted, unlock AlgebraRestrict
							sign = POSITIVE;	//operator inserted, reset SIGN_SWAP
							if (isOpratr) RightParenthesis = false;
							// not adjacent to Parenthesis
							//isDigit = false;
						}
						// parenthesis check
						if	(bc == LEFT_PRN) { ++Open_parenthesis; LeftParenthesis = true; }
						else LeftParenthesis = false;
						if	(bc == RIGHT_PRN) { --Open_parenthesis; RightParenthesis = true; }
						if (RightParenthesis && (isDigit || isAlgebra)) break; // can't concatenate digits with argebra
						
						//------------ Number Insersion ------------//
						// input character
						stream << (char)bc;
						++InsertedCharacters;
						
						if (!isDigit)
						{ stream << ' '; ++InsertedCharacters; }
						
						OpInserted = (isOpratr)? true : false;
						DigitInserted = (isDigit)? true : false;
						
					
				
			}
		}
			break;
			
		case FACTORIAL:
		{
			if (ResultOutputted || PowerON || FN_ON || CmplxON || SqrtON) break;
			if (!FactorialON)
			{
				if (!stream.str().empty())
				{
					// char last = stream.str().back();
					if (!OpInserted && !LeftParenthesis) break;
				}
				stream << "[]!";
				FactorialON		= true;
				DotInserted		= true; // no dot insertion is allowed
				InsertedCharacters += 3;
			}
			else
			{
				string base = stream.str().substr(stream.str().find_last_of("["));
				base.erase(base.find("["), 1);
				base.pop_back(); base.pop_back();
				if (Integer(base) > 10000)
				{
					stream.str("");
					stream << "Sorry, It'll take forever";
					ResultOutputted = true;
					PowerON			= false;
					AlgebraON		= false;
					FN_ON			= false;
					CmplxON			= false;
					Open_parenthesis = 0;
				}
				else
				{
					
					if (base == "") //stream.str("");
					{
						string tmp = stream.str();
						tmp.erase(tmp.length() - 3, 3);
						stream.str("");
						stream << tmp;
						InsertedCharacters -= 3;
					}
					else
						stream << " ";
					
				}
				FactorialON = false;
				DotInserted = false;
				OpInserted  = false;
			}
			break;
		}
		case POWER:
		{
			
			if (ResultOutputted || FactorialON || FN_ON || CmplxON || SqrtON) break;
			string tmp = stream.str();
			if (!tmp.empty() && tmp.back() == ' ') { tmp.pop_back(); stream.str(""); stream << tmp; }
			
			if (!stream.str().empty())
			{
				char in = stream.str().back();
				if ((in >= ZERO && in <= NINE) || (in >= UA && in <= UC) || in == 'i')
				{// power mark must have digits or algebras on both sides
					if (!PowerON)
					{
						size_t pos;
						if ((pos = tmp.find_last_of(" ")) == string::npos) pos = 0;
						stream << " ^ ";
						PowerON		= true;
						DotInserted = true; // no dot insertion is allowed
					}
					else
					{
						stream << ' ';
						PowerON		= false;
						DotInserted = false; // unlock dot insertion
						AlgebraRestrict = true;
					}
				}
			}
			break;
		}
			
			
		case FN:
		{
			if (ResultOutputted || FactorialON || PowerON || CmplxON || SqrtON || InsertedCharacters) break;
			if (!FN_ON) FN_ON = true;
			else		FN_ON = false;
			break;
		}
			
			
		case COMPLEX:
		{
			if (ResultOutputted || FactorialON || PowerON || FN_ON || SqrtON) break;
			if (!CmplxON)
			{// it's on, input Real
				if (AlgebraRestrict) break;
				if (!stream.str().empty() && !OpInserted && RightParenthesis) break;
				CmplxParts = REAL;
				stream << " +i";
				CmplxON		= true;
				AlgebraRestrict = true;
				InsertedCharacters += 3;
			}
			else if (stream.str().substr(stream.str().find_last_of(" ")).at(1) == '+')
			{// nothing in real
				string tmp = stream.str();
				stream.str("");
				tmp.pop_back(); tmp.pop_back(); tmp.pop_back();
				stream << tmp;
				CmplxON = false;
				AlgebraRestrict = false;
				InsertedCharacters -= 3;
				CmplxParts = REAL;
			}
			else if (CmplxParts == REAL)
			{// done with Real, next input Imaginary
				CmplxParts = IMAG;
				sign = POSITIVE;
				DotInserted = false;
			}
			else if (((stream.str().find_last_of("+") != string::npos && stream.str().substr(stream.str().find_last_of("+")).at(1) != 'i') ||		(stream.str().find_last_of("-") != string::npos && stream.str().substr(stream.str().find_last_of("-")).at(1) != 'i'))
					 && CmplxParts == IMAG)
			{// termination
				stream << " ";
				CmplxParts = REAL;
				CmplxON = false;
			}
			break;
		}
			
			
		case SQRT:
		{
			if(ResultOutputted || FactorialON || PowerON || FN_ON || CmplxON) break;
			if (!SqrtON)
			{
				if (!stream.str().empty())
				{
					char last = stream.str().back();
					if ((last >= ZERO && last <= NINE) || (last >= UA && last <= UC)) break;
				}
				stream << "sqrt[  ]";
				SqrtON = true;
				InsertedCharacters += 6;
			}
			else if (stream.str().substr(stream.str().find_last_of("[")).at(2) == ' ')
			{
				string tmp = stream.str();
				stream.str("");
				tmp.erase(tmp.find_last_of("s"), 8);
				stream << tmp;
				SqrtON = false;
				InsertedCharacters -= 6;
			}
			else
			{
				string base = stream.str().substr(stream.str().find_last_of("sqrt["));
				base.erase(0, 1);
				base.pop_back();
				
				if (base == "") stream.str("");
				else stream << " ";
				
				SqrtON = false;
				OpInserted = false;
			}
			break;
		};
			
		case SWAP_SIGN: {
			if (!ResultOutputted && !PowerON) {
				string line = stream.str();
				size_t pos = 0;
				if (SqrtON) break;
				if (CmplxParts == IMAG)
				{
					if (sign == POSITIVE) {
						sign = NEGATIVE;
						pos = stream.str().find_last_of("+");
						line.erase(pos, 1);
						line.insert(pos, 1, '-');
					}
					else {
						sign = POSITIVE;
						pos = stream.str().find_last_of("-");
						line.erase(pos, 1);
						line.insert(pos, 1, '+');
					}
				}
				else
				{
					//if (AlgebraON && InsertedCharacters > 2) pos = stream.str().find_last_of("\n") + 1;
					if (stream.str().find_last_of(" ") != string::npos) pos = stream.str().find_last_of(" ") + 1;
					
					if (sign == POSITIVE) {
						sign = NEGATIVE;
						line.insert(pos, 1, '-');
						++InsertedCharacters;
					}
					else {
						sign = POSITIVE;
						line.erase(pos, 1);
						--InsertedCharacters;
					}
				}
				stream.str("");
				stream << line;
			}
		}
			break;
			
		case INSERT_DOT: {
			if (!ResultOutputted) {
				if (!DotInserted && InsertedCharacters>0 && InsertedCharacters<300) {
					DotInserted = true;
					++InsertedCharacters;
					if (CmplxON)
					{
						string tmp = stream.str();
						if (CmplxParts == REAL)  tmp.insert(tmp.find_last_of("+"), 1, '.');
						else if (CmplxParts == IMAG) tmp.insert(tmp.find_last_of("i"), 1, '.');
						stream.str("");
						stream << tmp;
					}
					else if (SqrtON)
					{
						string tmp = stream.str();
						tmp.pop_back(); tmp.pop_back();
						tmp = tmp + ". ]";
						stream.str("");
						stream << tmp;
					}
					else
						stream << '.';
				}
			}
		}
			break;
			
		case CLEAR:
			if (!PrecValue) { delete PrecValue; PrecValue = NULL; }
			if (!Value) { delete Value; Value = NULL; }
			DotInserted = false;
			InsertedCharacters = 0;
			sign = POSITIVE;
			SignString.setString("");
			stream.str("");
			ResultOutputted = false;
			FactorialON		= false;
			PowerON			= false;
			SqrtON			= false;
			AlgebraON		= false;
			FN_ON			= false;
			CmplxON			= false;
			AlgebraRestrict = false;
			RightParenthesis = false;
			OpInserted = false;
			DigitInserted = false;
			Open_parenthesis = 0;
			Op = NONE;
			break;
			
		case EQUAL: {
			if (Open_parenthesis)
			{
				stream.str("");
				stream << "Open parenthesis exits";
				DotInserted = false;
				InsertedCharacters = 0;
				sign = POSITIVE;
				ResultOutputted = true;
				FactorialON = false;
				PowerON = false;
				SqrtON = false;
				AlgebraON = false;
				FN_ON = false;
				CmplxON = false;
				AlgebraRestrict = false;
				RightParenthesis = false;
				OpInserted = false;
				DigitInserted = false;
				Open_parenthesis = 0;
				Op = NONE;
				
				break;
			}
			
			string line = stream.str();
			char AG = '\0';
			
			if (AlgebraON)
			{
				AG = stream.str().front();
				line.erase(0, 3); // erase "X= "
				if (line == "") stream << '0';
				size_t p;
				while ((p = line.find("\n")) != string::npos)
				{
					line.erase(p, 1);
				}
				line = "( " + line + " )";
				bool fully_expand = false;
				size_t pos(0), pos1(0), pos2(0), pos3(0);
				cout << "Original input: " << line << endl;
				
				
				while (!fully_expand)
				{
					if ((pos1 = line.find("A")) != string::npos) { line.erase(pos1, 1); line.insert(pos1, A); }
					if ((pos2 = line.find("B")) != string::npos) { line.erase(pos2, 1); line.insert(pos2, B); }
					if ((pos3 = line.find("C")) != string::npos) { line.erase(pos3, 1); line.insert(pos3, C); }
					if (pos1 == string::npos && pos2 == string::npos && pos3 == string::npos) fully_expand = true;
				}
				
			}
			
			if (!ResultOutputted || AlgebraON) {
				
				string pf = lineParser(line);
				string tkn;
				stack<NumberObject*> stk;
				size_t pos = 0;
				bool last = false;
				NumberObject *result = NULL;
				
				///////////////////////////// postfix arithmetic ////////////////////////////
				while (!last)
				{
					if ((pos = pf.find(" ")) == string::npos)
					{
						tkn = pf; last = true;
					}
					else
					{
						tkn = pf.substr(0, pos);
						pf.erase(0, pos + 1);
					}
					if (tkn == "Invalid_Format") { result = new Integer;  result->setNum("Invalid Format"); }
					
					while (1)
					{
						
						if (tkn == "+" || tkn == "-" || tkn == "*" || tkn == "/" || tkn == "^" || tkn == "!" || tkn == "sqrt")
						{
							//if (Value) { delete Value; Value = NULL; }
							if (PrecValue) { delete PrecValue; PrecValue = NULL; }
							// creating Value
							if (stk.empty())
							{
								stream.str("");
								stream << "Invalid Format";
								ResultOutputted = true;
								return;
							}
							else
							{
								Value = stk.top();
								stk.pop();
							}
							// creating PrecValue
							if (tkn == "!" || tkn == "sqrt"); // do nothing
							else if (stk.empty())
							{
								stream.str("");
								stream << "Invalid Format";
								ResultOutputted = true;
								return;
							}
							else
							{
								PrecValue = stk.top();
								stk.pop();
							}
							
							
							//result = Value;
							stream.str("");
							
							Op = static_cast<Operator>(static_cast<int>(tkn[0]));
							
							////////////////////////////////////    main operations     ///////////////////////////////////////
							
							switch (Op) {
								case ADD:
								{
									
									if		(PrecValue->getType() == 'i' && Value->getType() == 'i')
										result = new Integer(*(Integer*)PrecValue + *(Integer*)Value);
									else if (PrecValue->getType() == 'i' && Value->getType() == 'd')
										result = new Decimal(*(Integer*)PrecValue + *(Decimal*)Value);
									else if (PrecValue->getType() == 'i' && Value->getType() == 'c')
										result = &(*(Integer*)PrecValue + *(Complex*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
										result = new Decimal(*(Decimal*)PrecValue + *(Integer*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
										result = new Decimal(*(Decimal*)PrecValue + *(Decimal*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'c')
										result = &(*(Decimal*)PrecValue + *(Complex*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'i')
										result = &(*(Complex*)PrecValue + *(Integer*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'd')
										result = &(*(Complex*)PrecValue + *(Decimal*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'c')
										result = &(*(Complex*)PrecValue + *(Complex*)Value);
									break;
									 
								}
								case SUBTRACT:
								{
									if		(PrecValue->getType() == 'i' && Value->getType() == 'i')
										result = new Integer(*(Integer*)PrecValue - *(Integer*)Value);
									else if (PrecValue->getType() == 'i' && Value->getType() == 'd')
										result = new Decimal(*(Integer*)PrecValue - *(Decimal*)Value);
									else if (PrecValue->getType() == 'i' && Value->getType() == 'c')
										result = &(*(Integer*)PrecValue - *(Complex*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
										result = new Decimal(*(Decimal*)PrecValue - *(Integer*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
										result = new Decimal(*(Decimal*)PrecValue - *(Decimal*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'c')
										result = &(*(Decimal*)PrecValue - *(Complex*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'i')
										result = &(*(Complex*)PrecValue - *(Integer*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'd')
										result = &(*(Complex*)PrecValue - *(Decimal*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'c')
										result = &(*(Complex*)PrecValue - *(Complex*)Value);
									break;
								}
								case MULTIPLY:
								{
									if		(PrecValue->getType() == 'i' && Value->getType() == 'i')
										result = new Integer(*(Integer*)PrecValue * *(Integer*)Value);
									else if (PrecValue->getType() == 'i' && Value->getType() == 'd')
										result = new Decimal(*(Integer*)PrecValue * *(Decimal*)Value);
									else if (PrecValue->getType() == 'i' && Value->getType() == 'c')
										result = &(*(Integer*)PrecValue * *(Complex*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
										result = new Decimal(*(Decimal*)PrecValue * *(Integer*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
										result = new Decimal(*(Decimal*)PrecValue * *(Decimal*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'c')
										result = &(*(Decimal*)PrecValue * *(Complex*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'i')
										result = &(*(Complex*)PrecValue * *(Integer*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'd')
										result = &(*(Complex*)PrecValue * *(Decimal*)Value);
									else if (PrecValue->getType() == 'c' && Value->getType() == 'c')
										result = &(*(Complex*)PrecValue * *(Complex*)Value);
									break;
								}
								case DIVIDE:
									try {
										if		(PrecValue->getType() == 'i' && Value->getType() == 'i')
											result = new Decimal(*(Integer*)PrecValue / *(Integer*)Value);
										else if (PrecValue->getType() == 'i' && Value->getType() == 'd')
											result = new Decimal(*(Integer*)PrecValue / *(Decimal*)Value);
										else if (PrecValue->getType() == 'i' && Value->getType() == 'c')
											result = &(*(Integer*)PrecValue / *(Complex*)Value);
										else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
											result = new Decimal(*(Decimal*)PrecValue / *(Integer*)Value);
										else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
											result = new Decimal(*(Decimal*)PrecValue / *(Decimal*)Value);
										else if (PrecValue->getType() == 'd' && Value->getType() == 'c')
											result = &(*(Decimal*)PrecValue / *(Complex*)Value);
										else if (PrecValue->getType() == 'c' && Value->getType() == 'i')
											result = &(*(Complex*)PrecValue / *(Integer*)Value);
										else if (PrecValue->getType() == 'c' && Value->getType() == 'd')
											result = &(*(Complex*)PrecValue / *(Decimal*)Value);
										else if (PrecValue->getType() == 'c' && Value->getType() == 'c')
											result = &(*(Complex*)PrecValue / *(Complex*)Value);
									}
									catch (const invalid_argument &e)
								{
									string m = e.what();
									result = new Integer(m);
								}
									break;
									
								case POW:
									
									try
									{
										int p = atoi(Value->getNum().c_str()) * Value->getSign();
										if		(PrecValue->getType() == 'i' && Value->getType() == 'i')
											result = new Integer(Power(*(Integer*)PrecValue, p));
										else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
											result = new Decimal(Power(*(Decimal*)PrecValue, p));
										else if (PrecValue->getType() == 'c' && Value->getType() == 'i')
											result = &Power(*(Complex*)PrecValue, p);
									}
									catch (invalid_argument e)
									{
										string m = e.what();
										result = new Integer(m);
									}
									
									break;
									
								case SQT:
									try
									{
										if		(Value->getType() == 'i')
											result = new Decimal(Power(*(Integer*)Value, 0.5));
										else if (Value->getType() == 'd')
											result = new Decimal(Power(*(Decimal*)Value, 0.5));
										else if (Value->getType() == 'c')
											result = &(Power(*(Complex*)Value, 0.5));;
									}
									catch (invalid_argument e)
									{
										string m = e.what();
										result = new Integer(m);
									}
									break;
								case FCT:
									try
								{
									if (Value->getType() != 'i')
									{
										Value = new Integer;
										Value->setNum("Only Integer supports factorial function!");
										last = true;
									}
									else if (10000 >= *(Integer*)Value)
									{
										Integer::Factorial(*(Integer*)Value);
									}
									else
									{
										Value->setNum("Sorry, It'll take forever");
										last = true;
									}
									result = Value;
								}
									catch (invalid_argument e)
								{
									delete Value;
									string m = e.what();
									result = new Integer(m);
								}
									break;
									
								default: break;
							} // end of switch
							break;
						}// end of if		( is Ops)
						else
						{
							////// Creating corresponding objects //////
							if (tkn == "") break;
							if (tkn.find("i") != string::npos)
							{
								stk.push(new Complex(tkn));
							}
							else if ((tkn.find(".") != string::npos) || (tkn.find("/") != string::npos))
							{
								stk.push(new Decimal(tkn));
							}
							else
							{
								stk.push(new Integer(tkn));
							}
							
							break;
						}
					}// end of infinite loop
					if (result)
					{
						stk.push(result);
						result = NULL;
					}
				}//end of while
				
				
				result = stk.top();
				stream.str("");
				
				/////////////////// A N S W E R /////////////////////
				
				if (AlgebraON)
				{
					string tmp;
					switch (result->getType())
					{
						case 'i':
							tmp = result->getNum();
							break;
						case 'd':
							tmp = result->getNum();
							break;
						case 'c':
							tmp = result->getNum() + "i";
							if (((Complex*)result)->getImagSign() == -1)
							{
								size_t plusSignPos = tmp.find("+");
								tmp.erase(plusSignPos, 1);
								tmp.insert(plusSignPos, "-");
							}
						default:
							break;
					}
					if		(tmp == "Invalid Format" || tmp == "Invalid input" || tmp == "Open parenthesis exits" || tmp == "Sorry, it'll take forever!")
					{ stream.str(""); stream << tmp; tmp = "0"; ResultOutputted = true; }
					else
					{
						if (result->getSign() == -1) tmp = "-" + tmp;
						switch (AG)
						{
							case 'A':		A = tmp; break;
							case 'B':		B = tmp; break;
							case 'C':		C = tmp; break;
							default:		break;
						}
						stream.str("");
						ResultOutputted = false;
					}
					cout << "------------------------------------------------" << endl
					<< "Algebra(" << AG << ") : " << tmp << endl << endl;
					
					
				}
				else
				{
					switch (result->getType())
					{
						case 'i':		stream << *(Integer*)result; break;
						case 'd':		stream << *(Decimal*)result; break;
						case 'c':		stream << *(Complex*)result; break;
						default:		break;
					}
					
					// console display
					cout << "------------------------------------------------" << endl
					<< "Full output : " << endl << *result << endl << endl;
					
					// word wrapping
					size_t len = stream.str().length();
					string tmp = stream.str();
					
					if (len >= 300)
					{
						len = 300;
						tmp.erase(tmp.begin() + 300, tmp.end());
					}
					for (size_t i = 1, delimiter = 60; i <= (len / 60) && i < 5; i++, delimiter++)
					{
						tmp.insert(delimiter, 1, '\n');
						delimiter += 60;
					}
					stream.str("");
					stream << tmp;
					ResultOutputted = true;
				}
				result = NULL;
				while (!stk.empty()) { delete stk.top(); stk.pop(); } // clear stack
				
				// if (Value) { delete Value; Value = NULL; }
				DotInserted = false;
				InsertedCharacters = 0;
				sign = POSITIVE;
				//ResultOutputted = true;
				FactorialON = false;
				PowerON = false;
				SqrtON = false;
				AlgebraON = false;
				FN_ON = false;
				CmplxON = false;
				AlgebraRestrict = false;
				RightParenthesis = false;
				OpInserted = false;
				DigitInserted = false;
				Open_parenthesis = 0;
				Op = NONE;
			}
			break;
		}
		default: break;
			
	}
	
}

string Calculator::lineParser(const string &line)
{
	string stack, postfix, infix, tkn;
	infix = line;
	size_t pos = 0;
	int prn = 0;
	bool first = true;
	bool last = false;
	// remove '\n'
	while (infix.find("\n") != string::npos) infix.erase(infix.find("\n"), 1);
	// insert algebra
	while ((pos = infix.find("A")) != string::npos)
	{
		infix.erase(pos, 1);
		infix.insert(pos, A);
	}
	while ((pos = infix.find("B")) != string::npos)
	{
		infix.erase(pos, 1);
		infix.insert(pos, B);
	}
	while ((pos = infix.find("C")) != string::npos)
	{
		infix.erase(pos, 1);
		infix.insert(pos, C);
	}
	
	cout << "Infix   : " << infix << endl;
	
	
	while (!last)
	{
		if ((pos = infix.find(" ")) == string::npos)
		{
			// cout << "cannot find space" << endl;
			tkn = infix; last = true;
		}
		else
		{
			tkn = infix.substr(0, pos);
			infix.erase(0, pos + 1);
		}
		while (1)
		{
			// nothing in a complex number
			if (tkn == "+i" || tkn == "-+i") break;
			// get rid of '[' and ']' of a factorial
			else if (tkn.find("]!") != string::npos) { tkn.erase(tkn.find("["), 1); tkn.insert(tkn.find("]"), " "); tkn.erase(tkn.find("]"), 1); }
			else if	(tkn == "(")
			{// '('
				if (!stack.empty() && (stack.back() == '*' || stack.back() == '/' || stack.back() == '+' || stack.back() == '-' || stack.back() == '(' || stack.back() == '['))
				{
					stack.push_back('(');
					prn++;
					break;
				}
				else if (stack.empty() && !postfix.empty() &&(postfix.back() == '+' || postfix.back() == '-' || postfix.back() == '*' || postfix.back() == '/'))
				{
					stack.push_back('(');
					prn++;
					break;
				}
				else if (stack.empty() && first)
				{
					stack.push_back('(');
					prn++;
					break;
				}
				else return "Invalid_Format";
			}
			else if (tkn == "+" || tkn == "-")
			{// '+' , '-'
				if (!stack.empty() && (stack.back() == '*' || stack.back() == '/' || stack.back() == '+' || stack.back() == '-' || stack.back() == '^'))
				{
					postfix = postfix + " ";
					postfix.push_back(stack.back());
					stack.pop_back();
				}
				else
				{
					stack.push_back(tkn[0]);
					break;
				}
				
			}
			else if (tkn == "*" || tkn == "/")
			{// '*' , '/'
				if (!stack.empty() && (stack.back() == '*' || stack.back() == '/' || stack.back() == '^'))
				{
					postfix = postfix + " ";
					postfix.push_back(stack.back());
					stack.pop_back();
				}
				else
				{
					stack.push_back(tkn[0]);
					break;
				}
			}
			else if (tkn == "^") { stack.push_back(tkn[0]); break; }
			else if (tkn == ")")
			{// ')'
				while (!stack.empty() && stack.back() != '(')
				{
					postfix = postfix + " ";
					postfix.push_back(stack.back());
					stack.pop_back();
				}
				if (!stack.empty())
				{
					stack.pop_back(); // pop '('
					prn--;
				}
				else return "Invalid_Format";
				break;
			}
			else if (tkn == "sqrt[")
			{
				stack.push_back('[');
				break;
			}
			else if (tkn == "]")
			{// ']'
				stack.pop_back(); // pop '['
				postfix = postfix + " sqrt";
				break;
			}
			else
			{
				postfix = postfix + " " + tkn;
				break;
			}
			
		}// end of infinite loop
		first = false;
	}// end of while
	
	while (!stack.empty())
	{
		if (stack.back() != '(')
		{
			postfix = postfix + " ";
			postfix.push_back(stack.back());
		}
		stack.pop_back();
	}
	
	// cout << stack << endl;
	cout << "Postfix :" << postfix << endl;
	
	if (postfix == " ") return "Invalid_Format";
	else if (prn == 0) return postfix;
	else return "Invalid_Format";
	
}
