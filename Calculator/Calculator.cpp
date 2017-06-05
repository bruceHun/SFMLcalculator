

#include "Calculator.h"

#include <iostream>
#include <sstream> //Needed for std::ostringstream
#include <cmath>
#include <queue>
#include <stdexcept>

using std::cout;

namespace
{
	sf::Font font;
	short regPressed, opPressed, exPressed, fnPressed;
}


//Class Constructor
Calculator::Calculator() :
	//Inizialize class members
	PrecValue(0),
	Value(0),
	A("0"),
	B("0"),
	C("0"),
	DotInserted(false),
	OpInserted(false),
	DigitInserted(false),
	Op(NONE),
	InsertedCharacters(0),
	stream(""),
	sign(POSITIVE),
	CmplxParts(REAL),
	ResultOutputted(false),
	FactorialON(false),
	PowerON(false),
	SqrtON(false),
	FN_ON(false),
	CmplxON(false),
	AlgebraRestrict(false),
	LeftParenthesis(false),
	RightParenthesis(false),
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
	// loading font
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
	Display.second.setPosition(70 , 75); //Set the position of the text in the display
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
		case 0:		button_text = "7"; break;
		case 1:		button_text = "8"; break;
		case 2:		button_text = "9"; break;
		case 3:		button_text = "4"; break;
		case 4:		button_text = "5"; break;
		case 5:		button_text = "6"; break;
		case 6:		button_text = "1"; break;
		case 7:		button_text = "2"; break;
		case 8:		button_text = "3"; break;
		case 9:		button_text = "+/-"; break;
		case 10:	button_text = "0"; break;
		case 11:	button_text = "."; break;
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
		case 0:		button_text = "n!"; break;
		case 1:		button_text = "rt"; break;
		case 2:		button_text = "A"; break;
		case 3:		button_text = "FN"; break;
		case 4:		button_text = "pw"; break;
		case 5:		button_text = "B"; break;
		case 6:		button_text = "("; break;
		case 7:		button_text = ")"; break;
		case 8:		button_text = "C"; break;
		case 9:		button_text = ""; break;
		case 10:	button_text = ""; break;
		case 11:	button_text = "i"; break;
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
				if			(x >= 50 && x <= 110) {
					if		(y >= 150 && y <= 210) { InsertCharacter(SEVEN); regPressed = 0; }
					else if (y >= 240 && y <= 300) { InsertCharacter(FOUR); regPressed = 3; }
					else if (y >= 330 && y <= 390) { InsertCharacter(ONE); regPressed = 6; }
					else if (y >= 420 && y <= 480) { InsertCharacter(SWAP_SIGN);  regPressed = 9; }
				}
				else if		(x >= 140 && x <= 200) {
					if		(y >= 150 && y <= 210) { InsertCharacter(EIGHT); regPressed = 1; }
					else if (y >= 240 && y <= 300) { InsertCharacter(FIVE); regPressed = 4; }
					else if (y >= 330 && y <= 390) { InsertCharacter(TWO); regPressed = 7; }
					else if (y >= 420 && y <= 480) { InsertCharacter(ZERO); regPressed = 10; }
				}
				else if		(x >= 230 && x <= 290) {
					if		(y >= 150 && y <= 210) { InsertCharacter(NINE); regPressed = 2; }
					else if (y >= 240 && y <= 300) { InsertCharacter(SIX); regPressed = 5; }
					else if (y >= 330 && y <= 390) { InsertCharacter(THREE); regPressed = 8; }
					else if (y >= 420 && y <= 480) { InsertCharacter(INSERT_DOT); regPressed = 11; }
				}
	
				else if		(x >= 320 && x <= 380) {
					if		(y >= 150 && y <= 210) { InsertCharacter(FACTORIAL); }
					else if (y >= 240 && y <= 300) { InsertCharacter(FN); }
					else if (y >= 330 && y <= 390) { InsertCharacter(LEFT_PRN); fnPressed = 6; }
					else if (y >= 420 && y <= 480) { InsertCharacter(LEFT_SHIFT); }
				}
				else if		(x >= 410 && x <= 470) {
					if		(y >= 150 && y <= 210) { InsertCharacter(SQRT); }
					else if (y >= 240 && y <= 300) { InsertCharacter(POWER); }
					else if (y >= 330 && y <= 390) { InsertCharacter(RIGHT_PRN); fnPressed = 7; }
					else if (y >= 420 && y <= 480) { InsertCharacter(RIGHT_SHIFT); }
				}
				else if		(x >= 500 && x <= 560) {
					if		(y >= 150 && y <= 210) { InsertCharacter(UA); fnPressed = 2; }
					else if (y >= 240 && y <= 300) { InsertCharacter(UB); fnPressed = 5; }
					else if (y >= 330 && y <= 390) { InsertCharacter(UC); fnPressed = 8; }
					else if (y >= 420 && y <= 480) { InsertCharacter(COMPLEX); }
				}
				
				else if		(x >= 590 && x <= 650) {
					if		(y >= 150 && y <= 210) { InsertCharacter(PLUS); opPressed = 0; }
					else if (y >= 240 && y <= 300) { InsertCharacter(MINUS); opPressed = 1; }
					else if (y >= 330 && y <= 390) { InsertCharacter(PER); opPressed = 2; }
					else if (y >= 420 && y <= 480) { InsertCharacter(SOLIDUS); opPressed = 3; }
				}
				else if		(x >= 680 && x <= 740) {
					if		(y >= 150 && y <= 300) { InsertCharacter(CLEAR); exPressed = 0; }
					else if (y >= 330 && y <= 480) { InsertCharacter(EQUAL); exPressed = 1; }
				}
			} //MouseClick
												break;
					
					///////////////// key binding /////////////////////
			case sf::Event::KeyPressed: { //Input by keyborad
				switch (Event.key.code) {
				case sf::Keyboard::A:			InsertCharacter(UA); fnPressed = 2; break;
				case sf::Keyboard::B:			InsertCharacter(UB); fnPressed = 5; break;
				case sf::Keyboard::C:			InsertCharacter(UC); fnPressed = 8; break;
				case sf::Keyboard::F:			InsertCharacter(FN); break;
				case sf::Keyboard::I:			InsertCharacter(COMPLEX); break;
				case sf::Keyboard::N:			InsertCharacter(FACTORIAL); break;
				case sf::Keyboard::P:			InsertCharacter(POWER); break;
				case sf::Keyboard::R:			InsertCharacter(SQRT); break;
				case sf::Keyboard::Num1: 
				case sf::Keyboard::Numpad1:		InsertCharacter(ONE); regPressed = 6; break;
				case sf::Keyboard::Num2: 
				case sf::Keyboard::Numpad2:		InsertCharacter(TWO); regPressed = 7; break;
				case sf::Keyboard::Num3: 
				case sf::Keyboard::Numpad3:		InsertCharacter(THREE); regPressed = 8; break;
				case sf::Keyboard::Num4: 
				case sf::Keyboard::Numpad4:		InsertCharacter(FOUR); regPressed = 3; break;
				case sf::Keyboard::Num5: 
				case sf::Keyboard::Numpad5:		InsertCharacter(FIVE); regPressed = 4; break;
				case sf::Keyboard::Num6: 
				case sf::Keyboard::Numpad6:		InsertCharacter(SIX); regPressed = 5; break;
				case sf::Keyboard::Num7: 
				case sf::Keyboard::Numpad7:		InsertCharacter(SEVEN); regPressed = 0; break;
				case sf::Keyboard::Num8: 
				case sf::Keyboard::Numpad8:		InsertCharacter(EIGHT); regPressed = 1; break;
				case sf::Keyboard::Num9: 
				case sf::Keyboard::Numpad9:		InsertCharacter(NINE); regPressed = 2; break;
				case sf::Keyboard::Num0: 
				case sf::Keyboard::Numpad0:		InsertCharacter(ZERO); regPressed = 10; break;
				case sf::Keyboard::LBracket:	InsertCharacter(LEFT_PRN); fnPressed = 6; break;
				case sf::Keyboard::RBracket:	InsertCharacter(RIGHT_PRN); fnPressed = 7; break;
				case sf::Keyboard::Period:
				case sf::Keyboard::Comma:		InsertCharacter(INSERT_DOT); regPressed = 11; break;
				case sf::Keyboard::BackSpace:	InsertCharacter(CLEAR); exPressed = 0; break;
				case sf::Keyboard::PageUp:
				case sf::Keyboard::PageDown:
				case sf::Keyboard::Home:
				case sf::Keyboard::End:
				case sf::Keyboard::LShift:		InsertCharacter(SWAP_SIGN); regPressed = 9; break;
				case sf::Keyboard::Equal:
				case sf::Keyboard::Add:			InsertCharacter(PLUS); opPressed = 0; break;
				case sf::Keyboard::Dash:
				case sf::Keyboard::Subtract:	InsertCharacter(MINUS); opPressed = 1; break;
				case sf::Keyboard::Multiply:	InsertCharacter(PER); opPressed = 2; break;
				case sf::Keyboard::Slash:
				case sf::Keyboard::Divide:		InsertCharacter(SOLIDUS); opPressed = 3; break;
				case sf::Keyboard::Return:		InsertCharacter(EQUAL); exPressed = 1; break;
				default: break;
				}
			} //KeyPressed
										break;
			default: break;
			} //Switch event.type
		} //Event Loop
		  /////////////////   Drawing	/////////////////
		Window.clear(sf::Color(77, 77, 77));
		for (unsigned i = 0; i < RegularButtons.size(); ++i) {
			if (regPressed == i)
			{
				RegularButtons.at(i).first.setFillColor(sf::Color::Black);
				RegularButtons.at(i).second.setFillColor(sf::Color::White);
			}
			else
			{
				RegularButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
				RegularButtons.at(i).second.setFillColor(sf::Color::Black);
			}
			
			Window.draw(RegularButtons[i].first);
			Window.draw(RegularButtons[i].second);
		}
		for (unsigned i = 0; i < OpButtons.size(); ++i) {
			if (opPressed == i)
			{
				OpButtons.at(i).first.setFillColor(sf::Color::Black);
				OpButtons.at(i).second.setFillColor(sf::Color::White);
			}
			else
			{
				OpButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
				OpButtons.at(i).second.setFillColor(sf::Color::Black);
			}
			
			Window.draw(OpButtons[i].first);
			Window.draw(OpButtons[i].second);
		}
		for (unsigned i = 0; i < ExButtons.size(); ++i) {
			if (exPressed == i)
			{
				ExButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
				ExButtons.at(i).second.setFillColor(sf::Color::Yellow);
			}
			else
			{
				ExButtons.at(i).first.setFillColor(sf::Color(255, 184, 77));
				ExButtons.at(i).second.setFillColor(sf::Color::Red);
			}
			
			Window.draw(ExButtons[i].first);
			Window.draw(ExButtons[i].second);
		}

		for (unsigned i = 0; i < FnButtons.size(); ++i) {
			
			switch (i)
			{// color switch
			case 0:
				if (FactorialON)
				{
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
					FnButtons.at(i).second.setFillColor(sf::Color::White);
				}
				else
				{
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
					FnButtons.at(i).second.setFillColor(sf::Color::Black);
				}
				break;
			case 1:
				if (SqrtON)
				{
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
					FnButtons.at(i).second.setFillColor(sf::Color::White);
				}
				else
				{
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
					FnButtons.at(i).second.setFillColor(sf::Color::Black);
				}
				break;
			case 3:
				if (FN_ON)
				{
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
					FnButtons.at(i).second.setFillColor(sf::Color::White);
				}
				else
				{
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
					FnButtons.at(i).second.setFillColor(sf::Color::Black);
				}
				break;
			case 4:
				if (PowerON)
				{
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
					FnButtons.at(i).second.setFillColor(sf::Color::White);
				}
				else
				{
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
					FnButtons.at(i).second.setFillColor(sf::Color::Black);
				}
				break;
			case 11:
				if (CmplxON)
				{
					if (CmplxParts == REAL)
					{
						FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
						FnButtons.at(i).second.setString("R");
						FnButtons.at(i).second.setFillColor(sf::Color::White);
					}
					else  if (CmplxParts == IMAG)
					{
						FnButtons.at(i).first.setFillColor(sf::Color(350, 20, 20));
						FnButtons.at(i).second.setString("i");
						FnButtons.at(i).second.setFillColor(sf::Color::White);
					}
				}
				else
				{
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
					FnButtons.at(i).second.setString("i");
					FnButtons.at(i).second.setFillColor(sf::Color::Black);
				}
				break;
					
			default:
				if (fnPressed == i)
				{
					FnButtons.at(i).first.setFillColor(sf::Color(224, 20, 20));
					FnButtons.at(i).second.setFillColor(sf::Color::White);
				}
				else
				{
					FnButtons.at(i).first.setFillColor(sf::Color(242, 242, 242));
					FnButtons.at(i).second.setFillColor(sf::Color::Black);
				}
				break;
			}
			
			Window.draw(FnButtons[i].first);
			Window.draw(FnButtons[i].second);
		}

		Window.draw(Display.first);
		
		regPressed = opPressed = exPressed = fnPressed = 100;
		
		///String processing
		//if (InsertedCharacters > 0 && InsertedCharacters < 300 && InsertedCharacters % 60 == 0) stream << '\n';
		if (stream.str().length() == 60) stream << " ";
		else if (InsertedCharacters && stream.str().length() < 300 && stream.str().length() % 61 == 0) stream << '\n';
		Display.second.setString(stream.str());
		//Display.second.SetCenter(Display.second.GetRect().GetWidth(), Display.second.GetRect().GetHeight()/2);
		Display.second.setOrigin(0 , Display.second.getLocalBounds().height / 2);
		Window.draw(Display.second);

		Window.display(); //Display window content
		sf::Time t = sf::seconds(0.05); //0.0166
		sf::sleep(t); //Wait a bit, avoid huge CPU usage
	} //While Running
}



