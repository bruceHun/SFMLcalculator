

#include "Calculator.h"

#include <iostream>
#include <sstream> //Needed for std::ostringstream
#include <cmath>
#include <queue>
#include <stdexcept>
using std::cout;

sf::Font font;

//Class Constructor
Calculator::Calculator() :
	//Inizialize class members
	PrecValue(0),
	Value(0),
	A(""),
	B(""),
	C(""),
	DotInserted(false),
	Op(NONE),
	InsertedCharacters(0),
	stream(""),
	sign(POSITIVE),
	IsFirstAlreadyReplaced(false),
	ResultOutputted(false),
	FactorialON(false),
	PowerON(false),
	FN_ON(false),
	CmplxON(false),
	AlgebraRestrict(false),
	Open_parenthesis(0)
{
	//Create the window
	Window.create(sf::VideoMode(790, 520, 32), "SFML Calculator", sf::Style::Close, sf::ContextSettings(24, 8));

	//Create the display
	Display.first = sf::RectangleShape(sf::Vector2f(695, 120));
	Display.first.setPosition(50, 20);
	Display.first.setFillColor(sf::Color(179, 204, 204));
	/* Create a rectangle which goes from (50,50)
	* to (470, 100). Its color is white (all
	* RGBA values are 255), and has a black outline
	* of 3px width
	*/
	
	if (!font.loadFromFile("/Library/Fonts/Arial.ttf"))
	{
		if (font.loadFromFile("C:/Windows/Fonts/arial.ttf"))
		{
			cout << "loaded \"C: / Windows / Fonts / arial.ttf\"" << endl;
		}
		else
		{
			exit(0);
		}
	}
	else
		cout << "loaded \"/Library/Fonts/Arial.ttf\"" << endl;

	Display.second = sf::Text("0", font, 20); //Current text in the display Text is 40px height
											  //Display.second.SetCenter(Display.second.GetRect().GetWidth(), Display.second.GetRect().GetHeight()/2);
	Display.second.setOrigin(Display.second.getLocalBounds().width, Display.second.getLocalBounds().height / 2);
	Display.second.setPosition(70 , 70); //Set the position of the text in the display
	Display.second.setFillColor(sf::Color::Black); //The text is black
												   //Same as before
	SignString = sf::Text("", font, 40);
	//SignString.SetSize(40);
	//SignString.SetCenter(0, SignString.GetRect().GetHeight()/2);
	SignString.setPosition(70, 70);
	SignString.setFillColor(sf::Color::Black);

	//Numbers' buttons
	for (short i = 0; i<12; ++i) {
		RegularButtons.push_back(std::pair <sf::RectangleShape, sf::Text>()); //Create a new buttons
																			  //Set buttons' coordinates
		int x1 = 50 + (i % 3) * 90, x2 = x1 + 60, y1 = 150 + i / 3 * 90, y2 = y1 + 60;
		RegularButtons.back().first = sf::RectangleShape(sf::Vector2f(80, 80));
		RegularButtons.back().first.setPosition(x1, y1);
		RegularButtons.back().first.setFillColor(sf::Color(242, 242, 242));
		//Set buttons' text
		std::string button_text;
		switch (i) {
		case 0: button_text = "7"; break;
		case 1: button_text = "8"; break;
		case 2: button_text = "9"; break;
		case 3: button_text = "4"; break;
		case 4: button_text = "5"; break;
		case 5: button_text = "6"; break;
		case 6: button_text = "1"; break;
		case 7: button_text = "2"; break;
		case 8: button_text = "3"; break;
		case 9: button_text = "+/-"; break;
		case 10: button_text = "0"; break;
		case 11: button_text = "."; break;
		default: break;
		}
		RegularButtons.back().second = sf::Text(button_text, font, 30);
		RegularButtons.back().second.setFillColor(sf::Color::Black);
		RegularButtons.back().second.setStyle(sf::Text::Bold);
		//RegularButtons.back().second.SetCenter(RegularButtons.back().second.GetRect().GetWidth()/2, RegularButtons.back().second.GetRect().GetHeight()/2); 
		RegularButtons.back().second.setOrigin(RegularButtons.back().second.getLocalBounds().width / 2, RegularButtons.back().second.getLocalBounds().height / 2);//Center the writing
		RegularButtons.back().second.setPosition(80 + 90 * (i % 3), 180 + 90 * (i / 3));
	}
	// FUNCTION BUTTONS
	for (short i = 0; i < 12; ++i) {
		FnButtons.push_back(std::pair <sf::RectangleShape, sf::Text>()); //Create a new buttons
																			  //Set buttons' coordinates
		//int x1 = 50 + (i % 2) * 90, x2 = x1 + 60, y1 = 150 + i / 2 * 90, y2 = y1 + 60;
		int x1 = 320 + 90 * ( i % 3), y1 = 150 + 90 * (i / 3);
		FnButtons.back().first = sf::RectangleShape(sf::Vector2f(80, 80));
		FnButtons.back().first.setPosition(x1, y1);
		FnButtons.back().first.setFillColor(sf::Color(242, 242, 242));
		//Set buttons' text
		std::string button_text;
		switch (i) {
		case 0: button_text = "n!"; break;
		case 1: button_text = "rt"; break;
		case 2: button_text = "A"; break;
		case 3: button_text = "FN"; break;
		case 4: button_text = "pw"; break;
		case 5: button_text = "B"; break;
		case 6: button_text = "("; break;
		case 7: button_text = ")"; break;
		case 8: button_text = "C"; break;
		case 9: button_text = ""; break;
		case 10: button_text = ""; break;
		case 11: button_text = "!"; break;
		default: break;
		}
		FnButtons.back().second = sf::Text(button_text, font, 30);
		FnButtons.back().second.setFillColor(sf::Color::Black);
		FnButtons.back().second.setStyle(sf::Text::Bold);
		//RegularButtons.back().second.SetCenter(RegularButtons.back().second.GetRect().GetWidth()/2, RegularButtons.back().second.GetRect().GetHeight()/2); 
		FnButtons.back().second.setOrigin(RegularButtons.back().second.getLocalBounds().width / 2, RegularButtons.back().second.getLocalBounds().height / 2);//Center the writing
		FnButtons.back().second.setPosition(350 + 90 * (i % 3), 180 + 90 * (i / 3));
	}

	//+,-,*,/
	for (short i = 0; i<4; ++i) {
		OpButtons.push_back(std::pair<sf::RectangleShape, sf::Text>());
		int x1 = 590, x2 = x1 + 60, y1 = 150 + i * 90, y2 = y1 + 60;
		OpButtons.back().first = sf::RectangleShape(sf::Vector2f(80, 80));
		OpButtons.back().first.setPosition(x1, y1);
		OpButtons.back().first.setFillColor(sf::Color(191, 191, 191));
		std::string button_text;
		switch (i) {
		case 0: button_text = "+"; break;
		case 1: button_text = "-"; break;
		case 2: button_text = "x"; break;
		case 3: button_text = "/"; break;
		default: break;
		}
		OpButtons.back().second = sf::Text(button_text, font, 30);
		OpButtons.back().second.setFillColor(sf::Color::Black);
		//OpButtons.back().second.SetSize(30);
		//OpButtons.back().second.SetCenter(OpButtons.back().second.GetRect().GetWidth()/2, OpButtons.back().second.GetRect().GetHeight()/2);
		OpButtons.back().second.setPosition(620, 180 + 90 * i);
		//OpButtons.back().second.setOrigin(OpButtons.back().second.getLocalBounds().width /2, OpButtons.back().second.getLocalBounds().height / 2);
		
	}
	//Clear, Equal
	for (short i = 0; i<2; ++i) {
		ExButtons.push_back(std::pair<sf::RectangleShape, sf::Text>());
		//int x1 = 410, x2 = x1 + 60, y1 = 150 + i * 180, y2 = y1 + 150;
		int x1 = 680 , y1 = 150 + i * 180;
		ExButtons.back().first = sf::RectangleShape(sf::Vector2f(65, 170));
		ExButtons.back().first.setPosition(x1, y1);
		ExButtons.back().first.setFillColor(sf::Color(255, 184, 77));
		if (i == 0) ExButtons.back().second = sf::Text("C", font, 30); //Clear button
		else ExButtons.back().second = sf::Text("=", font, 30);
		ExButtons.back().second.setFillColor(sf::Color::Red);
		//ExButtons.back().second.SetSize(30);
		//ExButtons.back().second.SetCenter(ExButtons.back().second.GetRect().GetWidth()/2, ExButtons.back().second.GetRect().GetHeight()/2);
		ExButtons.back().second.setPosition(700, 225 + i * 180);
	}
}

Calculator::~Calculator() {
	//Nothing to do
}

void Calculator::Start() {
	sf::Event Event; //Event handler
	bool Running = true; //Has the calculator go on running, or do we have to quit?
	while (Running) { //While we have to run
		while (Window.pollEvent(Event)) { //Read the events (key presses, mouse clicks, etc.)
			switch (Event.type) { //What happened? (A key has been pressed, X has been hit, etc.
			case sf::Event::Closed: //Red X or Alt+F4 pressed
				Running = false; break; //Quit
			case sf::Event::MouseButtonPressed: {//Mouse click (only with left button)
				int x = Event.mouseButton.x;
				int y = Event.mouseButton.y; //Mouse position
											 //Check if a button has been pressed, and eventually elaborate it
				////////////////// mouse click binding ////////////////////
				if (x >= 50 && x <= 110) {
					if (y >= 150 && y <= 210) InsertCharacter(SEVEN);
					else if (y >= 240 && y <= 300) InsertCharacter(FOUR);
					else if (y >= 330 && y <= 390) InsertCharacter(ONE);
					else if (y >= 420 && y <= 480) InsertCharacter(SWAP_SIGN);
				}
				else if (x >= 140 && x <= 200) {
					if (y >= 150 && y <= 210)  InsertCharacter(EIGHT);
					else if (y >= 240 && y <= 300) InsertCharacter(FIVE);
					else if (y >= 330 && y <= 390) InsertCharacter(TWO);
					else if (y >= 420 && y <= 480) InsertCharacter(ZERO);
				}
				else if (x >= 230 && x <= 290) {
					if (y >= 150 && y <= 210)  InsertCharacter(NINE);
					else if (y >= 240 && y <= 300) InsertCharacter(SIX);
					else if (y >= 330 && y <= 390) InsertCharacter(THREE);
					else if (y >= 420 && y <= 480) InsertCharacter(INSERT_DOT);
				}
	
				else if (x >= 320 && x <= 380) {
					if (y >= 150 && y <= 210)  InsertCharacter(FACTORIAL);
					else if (y >= 240 && y <= 300) InsertCharacter(FN);
					else if (y >= 330 && y <= 390) InsertCharacter(LEFT_PRN);
					else if (y >= 420 && y <= 480) InsertCharacter(LEFT_SHIFT);
				}
				else if (x >= 410 && x <= 470) {
					if (y >= 150 && y <= 210)  InsertCharacter(SQRT);
					else if (y >= 240 && y <= 300) InsertCharacter(POWER);
					else if (y >= 330 && y <= 390) InsertCharacter(RIGHT_PRN);
					else if (y >= 420 && y <= 480) InsertCharacter(RIGHT_SHIFT);
				}
				else if (x >= 500 && x <= 560) {
					if (y >= 150 && y <= 210)  InsertCharacter(UA);
					else if (y >= 240 && y <= 300) InsertCharacter(UB);
					else if (y >= 330 && y <= 390) InsertCharacter(UC);
					else if (y >= 420 && y <= 480) InsertCharacter(COMPLEX);
				}
				
				else if (x >= 590 && x <= 650) {
					if (y >= 150 && y <= 210)  InsertCharacter(PLUS);
					else if (y >= 240 && y <= 300) InsertCharacter(MINUS);
					else if (y >= 330 && y <= 390) InsertCharacter(PER);
					else if (y >= 420 && y <= 480) InsertCharacter(SOLIDUS);
				}
				else if (x >= 680 && x <= 740) {
					if (y >= 150 && y <= 300) InsertCharacter(CLEAR);
					else if (y >= 330 && y <= 480) InsertCharacter(EQUAL);
				}
			} //MouseClick
												break;
					
					///////////////// key binding /////////////////////
			case sf::Event::KeyPressed: { //Input by keyborad
				switch (Event.key.code) {
				case sf::Keyboard::Num1: 
				case sf::Keyboard::Numpad1:	InsertCharacter(ONE); break;
				case sf::Keyboard::Num2: 
				case sf::Keyboard::Numpad2:	InsertCharacter(TWO); break;
				case sf::Keyboard::Num3: 
				case sf::Keyboard::Numpad3:	InsertCharacter(THREE); break;
				case sf::Keyboard::Num4: 
				case sf::Keyboard::Numpad4:	InsertCharacter(FOUR); break;
				case sf::Keyboard::Num5: 
				case sf::Keyboard::Numpad5:	InsertCharacter(FIVE); break;
				case sf::Keyboard::Num6: 
				case sf::Keyboard::Numpad6:	InsertCharacter(SIX); break;
				case sf::Keyboard::Num7: 
				case sf::Keyboard::Numpad7:	InsertCharacter(SEVEN); break;
				case sf::Keyboard::Num8: 
				case sf::Keyboard::Numpad8:	InsertCharacter(EIGHT); break;
				case sf::Keyboard::Num9: 
				case sf::Keyboard::Numpad9:	InsertCharacter(NINE); break;
				case sf::Keyboard::Num0: 
				case sf::Keyboard::Numpad0:	InsertCharacter(ZERO); break;
				case sf::Keyboard::Period:
				case sf::Keyboard::Comma:		InsertCharacter(INSERT_DOT); break;
				case sf::Keyboard::PageUp:
				case sf::Keyboard::PageDown:
				case sf::Keyboard::Home:
				case sf::Keyboard::End:			InsertCharacter(SWAP_SIGN); break;
				case sf::Keyboard::Add:			InsertCharacter(PLUS); break;
				case sf::Keyboard::Subtract:	InsertCharacter(MINUS); break;
				case sf::Keyboard::Multiply:	InsertCharacter(PER); break;
				case sf::Keyboard::Divide:		InsertCharacter(SOLIDUS); break;
				case sf::Keyboard::Equal:
				case sf::Keyboard::Return:		InsertCharacter(EQUAL); break;
				default: break;
				}
			} //KeyPressed
										break;
			default: break;
			} //Switch event.type
		} //Event Loop

		  /////////////////   Drawing	/////////////////
		Window.clear(sf::Color(77, 77, 77));
		for (unsigned i = 0; i<RegularButtons.size(); ++i) {
			Window.draw(RegularButtons[i].first);
			Window.draw(RegularButtons[i].second);
		}
		for (unsigned i = 0; i<OpButtons.size(); ++i) {
			Window.draw(OpButtons[i].first);
			Window.draw(OpButtons[i].second);
		}
		for (unsigned i = 0; i<ExButtons.size(); ++i) {
			Window.draw(ExButtons[i].first);
			Window.draw(ExButtons[i].second);
		}

		for (unsigned i = 0; i<FnButtons.size(); ++i) {
			
			switch (i)
			{// color switch
			case 0:
				if (FactorialON)
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
				else
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
				break;
			case 3:
				if (FN_ON)
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
				else
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
				break;
			case 4:
				if (PowerON)
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
				else
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
				break;
			}
			Window.draw(FnButtons[i].first);
			Window.draw(FnButtons[i].second);
		}

		Window.draw(Display.first);

		///String processing
		//Window.draw(SignString);
		//Display.second = stream.str();
		Display.second.setString(stream.str());
		//Display.second.SetCenter(Display.second.GetRect().GetWidth(), Display.second.GetRect().GetHeight()/2);
		Display.second.setOrigin(0 , Display.second.getLocalBounds().height / 2);
		Window.draw(Display.second);

		Window.display(); //Display window content
		sf::Time t = sf::seconds(0.0166);
		sf::sleep(t); //Wait a bit, avoid huge CPU usage
	} //While Running
}

void Calculator::InsertCharacter(ButtonCode bc) {
	//Checks which button has been pressed
	switch (bc) {
		break;
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
	case  PER:
	case SOLIDUS:
		{
		if (!ResultOutputted) {
			if (Op == NONE || IsFirstAlreadyReplaced) {
				
				
				if (CmplxON) { // n! function is on
					if (bc != PER && bc != SOLIDUS && bc != LEFT_PRN && bc != RIGHT_PRN)
					{
						string line = stream.str();
						line.pop_back(); line.pop_back();
						stream.str("");
						stream << line << (char)bc << "!]";
					}
					break;
				}
				else if (PowerON) {	// pw function is on
					if (bc != PLUS && bc != MINUS && bc != PER && bc != SOLIDUS && bc != LEFT_PRN && bc != RIGHT_PRN)
					{
						stream << (char)bc;
					}
					break;
				}
				else if (FN_ON && !AlgebraON && (bc == 'A' || bc == 'B' || bc == 'C'))
				{// Algebra defining mode
					stream.str("");
					stream << (char)bc << "= ";
					FN_ON = false;
					AlgebraON = true;
					break;
				}
				if ((bc >= UA && bc <= UC))
				{
					if (!AlgebraRestrict)
					{
						if ((!stream.str().empty() && stream.str().back() >= ZERO && stream.str().back() <= NINE))
							break; // algebra can not follow a ditgit or a factorial
						AlgebraRestrict = true;
					}
					else break;
				}
				if		(FactorialON) { // n! function is on
					if (bc != PLUS && bc != MINUS && bc != PER && bc != SOLIDUS && bc != LEFT_PRN && bc != RIGHT_PRN)
					{
						string line = stream.str();
						line.pop_back(); line.pop_back();
						stream.str("");
						stream << line << (char)bc << ")!";
					}
					break;
				}
				
				
				//////////////////////// M A I N   I N S E R T I O N ////////////////////////
				if (InsertedCharacters<300) { // --------- max insert lenth ------------
					// word wrapping
					bool notDigit = false;
					if (bc == PLUS || bc == MINUS || bc == PER || bc == SOLIDUS || bc == LEFT_PRN || bc == RIGHT_PRN)
					{
						if (OpInserted && (bc >= PLUS && bc <= SOLIDUS)) break; // prevent concatenation of operators
						if (InsertedCharacters && ((stream.str().back() >= ZERO && stream.str().back() <= NINE) || (stream.str().back() >= UA && stream.str().back() <= UC)))
							stream << ' ';
						OpInserted = true;
						DotInserted = false; // another number, another dot
						AlgebraRestrict = false; // operator inserted, unlock AlgebraRestrict
						sign = POSITIVE;	//operator inserted, reset SIGN_SWAP
						notDigit = true;
					}
					
					//------------ Number Insersion ------------//
					if (InsertedCharacters > 0 && InsertedCharacters % 60 == 0) stream << '\n';
					// unlock operator insertion
					if (bc != PLUS && bc != MINUS && bc != PER && bc != SOLIDUS) OpInserted = false;
					// input character
					if	(AlgebraRestrict && bc >= ZERO && bc <= NINE) break; // can't concatenate digits with argebra
					stream << (char)bc;
					++InsertedCharacters;
					
					if (notDigit)
						stream << ' ';
					
					// parenthesis check
					if		(bc == LEFT_PRN) ++Open_parenthesis;
					else if	(bc == RIGHT_PRN) --Open_parenthesis;
				}
			}
			else if (Op != NONE && !(IsFirstAlreadyReplaced)) {
			
				//DotInserted = false;
				//InsertedCharacters = 0;
				IsFirstAlreadyReplaced = true;
				sign = POSITIVE;
				//stream.str("");
				stream << bc;
				++InsertedCharacters;
			}
		}
	}
			   break;
	
	case FACTORIAL:
		{
			if (!FactorialON)
			{
				char last = stream.str().back();
				if ((last >= ZERO && last <= NINE) || (last >= UA && last <=UC)) break;
				stream << "()!";
				FactorialON		= true;
				DotInserted		= true; // no dot insertion is allowed
				//AlgebraRestrict = true;
			}
			else
			{
				string base = stream.str().substr(stream.str().find_last_of("("));
				base.erase(0, 1);
				base.pop_back(); base.pop_back();
				if (Integer(base) > Integer(10000))
				{
					stream.str("");
					stream << "Sorry, It'll take forever";
					ResultOutputted = true;
					PowerON			= false;
					AlgebraON		= false;
					FN_ON			= false;
					CmplxON			= false;
					//AlgebraRestrict = false;
					Open_parenthesis = 0;
				}
				else
				{
					string f = stream.str();
					stream.str("");
					f.erase(f.find_last_of("("), 1); f.pop_back(); f.pop_back();
					stream << f << " ! ";
				}
				FactorialON = false;
				DotInserted = false;
				OpInserted = false;
			}
			break;
		}
	case POWER:
		{
			if (!stream.str().empty())
			{
				char in = stream.str().back();
				if ((in >= ZERO && in <= NINE) || (in >= UA && in <= UC))
				{// power mark must have digits or algebras on both sides
					if (!PowerON)
					{
						stream << " ^ ";
						PowerON		= true;
						DotInserted = true; // no dot insertion is allowed
					}
					else
					{
						stream << ' ';
						PowerON		= false;
						DotInserted = false; // unlock dot insertion
					}
				}
			}
			break;
		}
			
			
	case FN:
		{
			if (!FN_ON) FN_ON = true;
			else		FN_ON = false;
			break;
		}
			
			
	case COMPLEX:
		{
			if (!CmplxON)
			{
				//stream.str("");
				stream << "[!]";
				CmplxON		= true;
				//DotInserted = true; // no dot insertion is allowed
			}
			else
			{
				CmplxON		= false;
				//DotInserted = false;
			}
			break;
		}
			
			
	case SQRT:
		{
		if (PrecValue) { delete PrecValue; PrecValue = NULL; }
		if (Value) { delete Value; Value = NULL; }
		DotInserted = false;
		InsertedCharacters = 0;
		IsFirstAlreadyReplaced = false;
		sign = POSITIVE;
		SignString.setString("");
		stream.str("");
		stream.str("Working On it");
		ResultOutputted = false;
			FactorialON = false;
		break;
		}
	case SWAP_SIGN: {
		if (!ResultOutputted) {
			string line = stream.str();
			size_t pos = 0;
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
		IsFirstAlreadyReplaced = false;
		sign = POSITIVE;
		SignString.setString("");
		stream.str("");
		ResultOutputted = false;
		FactorialON		= false;
		PowerON			= false;
		AlgebraON		= false;
		FN_ON			= false;
		CmplxON			= false;
		AlgebraRestrict = false;
		Open_parenthesis = 0;
		break;
			
	case EQUAL: {
		if (Open_parenthesis)
		{
			stream.str("");
			stream << "Open parenthesis exits";
			DotInserted = false;
			InsertedCharacters = 0;
			IsFirstAlreadyReplaced = false;
			sign = POSITIVE;
			ResultOutputted = true;
			FactorialON = false;
			PowerON = false;
			AlgebraON = false;
			FN_ON = false;
			CmplxON = false;
			AlgebraRestrict = false;
			Open_parenthesis = 0;
			Op = NONE;
			
			break;
		}
		if (AlgebraON)
		{
			if (stream.str() == "") stream << '0';
			string line = stream.str();
			line.erase(0, 3);
			line = "( " + line + " )";
			bool fully_expand = false;
			size_t pos1(0), pos2(0), pos3(0);
			
			while (!fully_expand)
			{
				if ((pos1 = line.find("A")) != string::npos) { line.erase(pos1, 1); line.insert(pos1, A); }
				if ((pos2 = line.find("B")) != string::npos) { line.erase(pos2, 1); line.insert(pos2, B); }
				if ((pos3 = line.find("C")) != string::npos) { line.erase(pos3, 1); line.insert(pos3, C); }
				if (pos1 == string::npos && pos2 == string::npos && pos3 == string::npos) fully_expand = true;
			}
			switch (stream.str().front())
			{
			case 'A':		A = line; break;
			case 'B':		B = line; break;
			case 'C':		C = line; break;
			default:		break;
			}
					
			DotInserted = false;
			InsertedCharacters = 0;
			IsFirstAlreadyReplaced = false;
			sign = POSITIVE;
			ResultOutputted = false;
			FactorialON = false;
			PowerON = false;
			AlgebraON = false;
			FN_ON = false;
			CmplxON = false;
			AlgebraRestrict = false;
			Open_parenthesis = 0;
			Op = NONE;
			stream.str("");
			break;
		}
		
		if (!ResultOutputted) {
			
			string pf = lineParser(stream.str());
			string tkn;
			stack<NumberBase*> stk;
			size_t pos = 0;
			bool last = false;
			NumberBase *result = NULL;
			
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

				while (1)
				{
					if (tkn == "+" || tkn == "-" || tkn == "*" || tkn == "/" || tkn == "^" || tkn == "!")
					{
						//if (Value) { delete Value; Value = NULL; }
						if (PrecValue) { delete PrecValue; PrecValue = NULL; }
						// creating Value
						if (stk.empty()) 
						{
							stream.str("");
							stream << "Invalid Format";
							return;
						}
						else if (stk.top()->getNum().find(".") != string::npos)
						{
							Value = stk.top();
							stk.pop();
						}
						else if (stk.top()->getNum().find("+") != string::npos)
						{

						}
						/*
						else if (stk.top()->getNum().find("!") != string::npos)
						{
							string tmp = stk.top()->getNum();
							tmp.erase(0, 1);
							tmp.pop_back();
							tmp.pop_back();
							stk.top()->setNum(tmp);
							Integer::Factorial(*(Integer*)stk.top());
							Value = stk.top();
							stk.pop();
						}
						 */
						else
						{
							Value = stk.top();
							stk.pop();
						}
						// creating PrecValue
						if (tkn == "!"); // do nothing
						else if (stk.empty())
						{
							stream.str("");
							stream << "Invalid Format";
							return;
						}
						else if (stk.top()->getNum().find(".") != string::npos)
						{
							PrecValue = stk.top();
							stk.pop();
						}
						else if (stk.top()->getNum().find("+") != string::npos)
						{

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
							if (PrecValue->getType() == 'i' && Value->getType() == 'd')
								result = &(*(Integer*)PrecValue	 + *(Decimal*)Value);
							else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
								result = &(*(Decimal*)PrecValue + *(Integer*)Value);
							else if (PrecValue->getType() == 'i' && Value->getType() == 'i')
								result = &(*(Integer*)PrecValue	 + *(Integer*)Value);
							else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
								result = &(*(Decimal*)PrecValue + *(Decimal*)Value);
							break;
						}
						case SUBTRACT:
						{
							if (PrecValue->getType() == 'i' && Value->getType() == 'd')
								result = &(*(Integer*)PrecValue - *(Decimal*)Value);
							else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
								result = &(*(Decimal*)PrecValue - *(Integer*)Value);
							else if (PrecValue->getType() == 'i' && Value->getType() == 'i')
								result = &(*(Integer*)PrecValue - *(Integer*)Value);
							else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
								result = &(*(Decimal*)PrecValue - *(Decimal*)Value);
							break;
						}
						case MULTIPLY:
						{
							if (PrecValue->getType() == 'i' && Value->getType() == 'd')
								result = &(*(Integer*)PrecValue * *(Decimal*)Value);
							else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
								result = &(*(Decimal*)PrecValue * *(Integer*)Value);
							else if (PrecValue->getType() == 'i' && Value->getType() == 'i')
								result = &(*(Integer*)PrecValue * *(Integer*)Value);
							else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
								result = &(*(Decimal*)PrecValue * *(Decimal*)Value);
							break;
						}
						case DIVIDE:
							try {
								
									if (PrecValue->getType() == 'i' && Value->getType() == 'd')
										result = &(*(Integer*)PrecValue / *(Decimal*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'i')
										result = &(*(Decimal*)PrecValue / *(Integer*)Value);
									else if (PrecValue->getType() == 'i' && Value->getType() == 'i')
										result = &(*(Integer*)PrecValue / *(Integer*)Value);
									else if (PrecValue->getType() == 'd' && Value->getType() == 'd')
										result = &(*(Decimal*)PrecValue / *(Decimal*)Value);
									
									
								}catch (const invalid_argument &e)
								{
									cout << e.what();
									string m = e.what();
									result = new Integer(m);
								}
								break;
								
						case POW:
							{
								int p = atoi(Value->getNum().c_str());
								if (PrecValue->getType() == 'd' && Value->getType() == 'i')
									result = &(Power(*(Integer*)PrecValue, p));
								else if (PrecValue->getType() == 'i' && Value->getType() == 'i')
									result = &(Power(*(Integer*)PrecValue, p));
								break;
							}
						
						case FCT:
							{
								if (10000 >= *(Integer*)Value)
								{
									Integer::Factorial(*(Integer*)Value);
								}
								else
								{
									string a = "Sorry, It'll take forever";
									Value->setNum(a);
									last = true;
								}
								result = Value;
								break;
							}

						default: break;
						} // end of switch
						break;
					}// end of if		( is Ops)
					else
					{
						//// creating Value
						if (tkn == "") break;
						if (tkn.find(".") != string::npos)
						{
							stk.push(new Decimal(tkn));
						}
						else if (tkn.find("+") != string::npos)
						{

						}
						/*
						else if (tkn.find("^") != string::npos)
						{
							int power = atoi(tkn.substr(tkn.find("^") + 1).c_str());
							Integer *term = new Integer(tkn.substr(0, tkn.find("^")));
							*term = Power(*term, power);
							stk.push(term);
							
						}
						 
						
						else if (tkn.find(")!") != string::npos)
						{
							tkn.erase(0, 1);
							tkn.pop_back();
							tkn.pop_back();
							Integer *tmp = new Integer(tkn);
							Integer::Factorial(*tmp);
							stk.push(tmp);
						}
						*/
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
			if (Op == DIVIDE && Value == 0) { //We don't have to show the sign
				SignString.setString("");
			}
			else { //Show regular result
				
				// console display
				cout << ((result->getSign() > 0)? "" : "-") << stream.str() << endl;
				cout << *(Decimal*)result << endl;
				
				
				switch (result->getType())
				{
				case 'i':		stream << *(Integer*)result; break;
				case 'd':		stream << *(Decimal*)result; break;
				case 'c':		break;
				default:		break;
				}
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
				
				while (!stk.empty()) { delete stk.top(); stk.pop(); } // clear stack
			}
			//if (result) { delete result; result = NULL; }
			DotInserted = false;
			InsertedCharacters = 0;
			IsFirstAlreadyReplaced = false;
			sign = POSITIVE;
			ResultOutputted = true;
			FactorialON = false;
			PowerON = false;
			AlgebraON = false;
			FN_ON = false;
			CmplxON = false;
			AlgebraRestrict = false;
			Open_parenthesis = 0;
			Op = NONE;
		}
				break;
	default: break;
	}
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
	

	
	while (!last)
	{
		if ((pos = infix.find(" ")) == string::npos)
		{
			tkn = infix; last = true;
		}
		else
		{
			tkn = infix.substr(0, pos);
			infix.erase(0, pos + 1);
		}
		while (1)
		{
			if	(tkn == "(")
			{// '('
				if (!stack.empty() && (stack.back() == '*' || stack.back() == '/' || stack.back() == '+' || stack.back() == '-' || stack.back() == '('))
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
				if (!stack.empty() && (stack.back() == '*' || stack.back() == '/' || stack.back() == '+' || stack.back() == '-'))
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
			else if (tkn == "*" || tkn == "/" || tkn == "^")
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

	cout << stack << endl;
	cout << postfix << endl;

	if (postfix == " ") return "Invalid_Format";
	else if (prn == 0) return postfix;
	else return "Invalid_Format";
	
}

