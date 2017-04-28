/** SFML Calculator
** Compiled with: mingw-g++.exe version 4.7.1
** Compiling options required: -std=c++11
** Linking options: -s -lopengl32 -lsfml-graphics -lsfml-window -lsfml-system -lsfml-main
** Code optimized for visualization in CodeBlocks 12.11 RC1 IDE
*/

//include system and graphics SFML libraries
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
//Allow use of std::string instead of NULL-terminated char array
#include <string>
//Calculator class
#include "Calculator.h"

//Program entry point
int main() {
	//Create a Calculator named C
	Calculator C;
	C.Start(); //Call C's Start function
	return 0; //Exit
}
