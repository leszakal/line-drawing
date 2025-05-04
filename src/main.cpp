#include <iostream>
#include <string>
#include <limits>
#include <SDL3/SDL_main.h>
#include "menu.h"
#include "render.h"

int main(int argc, char* argv[]) {
	BresenhamLine bresenham = BresenhamLine();
	XiaolinWuLine wu = XiaolinWuLine();

	char input = '0';
	while (input != 'q') {
		showMainMenu();
		std::cin >> input;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');	// clear cin buffer
		std::cout << std::endl;
		if (input == 'q' || input == '4') {
			std::cout << "Exitting program...";
			exit(0);
		}
		else {
			try {
				if (!std::isdigit(input)) {
					throw std::string("ERROR: Input only numbers (1-4) or 'q' to quit\n");
				}
				int input_num = input - '0';
				switch (input_num)
				{
				case 1:
					showRenderPresetsMenu(bresenham, wu);
					break;
				case 2:
					showCustomRenderMenu(bresenham, wu);
					break;
				case 3:
					showTimeTestsMenu(bresenham, wu);
					break;
				default:
					throw std::string("ERROR: Invalid number. Enter 1-4 or 'q' to quit\n");
					break;
				}
			}
			catch (std::string e) {
				std::cout << e << std::endl;
			}
		}
	}

	return 0;
}