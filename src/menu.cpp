#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <chrono>
#include "menu.h"
#include "render.h"

void showMainMenu() {
	std::cout << "Please select an option below by entering its corresponding number:" << std::endl;
	std::cout << "===================================================================" << std::endl;
	std::cout << "1. Render preset lines" << std::endl;
	std::cout << "2. Render lines from custom endpoints" << std::endl;
	std::cout << "3. Run timed tests (no rendering)" << std::endl;
	std::cout << "4. Quit program" << std::endl;
	std::cout << std::endl;
	std::cout << "Enter a number: ";
}

void showRenderPresetsMenu(BresenhamLine bresenham, XiaolinWuLine wu) {
	char input;

	while (1) {
		std::vector<Point> bresenham_points;
		std::vector<Point> wu_points;

		std::cout << "Choose a line type by entering its corresponding number or enter 'q' to go back:" << std::endl;
		std::cout << "  1. Positive Slope" << std::endl;
		std::cout << "  2. Negative Slope" << std::endl;
		std::cout << "  3. Steep Positive Slope" << std::endl;
		std::cout << "  4. Steep Negative Slope" << std::endl;
		std::cout << "  5. Horizontal" << std::endl;
		std::cout << "  6. Vertical" << std::endl;
		std::cout << std::endl;
		std::cout << "Specify line type: ";
		std::cin >> input;
		std::cout << std::endl;

		if (input == 'q') {
			return;
		}
		else {
			try {
				if (!std::isdigit(input)) {
					throw std::string("ERROR: Input only numbers (1-6) or 'q' to go back\n");
				}
				int input_num = input - '0';
				switch (input_num)
				{
				case 1:
					bresenham.plotLine(bresenham_points, 0, 1, 1000, 450);
					wu.plotLine(wu_points, 0, 50, 1000, 500);
					createWindowAndRender(bresenham_points, wu_points);
					break;
				case 2:
					bresenham.plotLine(bresenham_points, 0, 100, 850, 0);
					wu.plotLine(wu_points, 0, 150, 850, 50);
					createWindowAndRender(bresenham_points, wu_points);
					break;
				case 3:
					bresenham.plotLine(bresenham_points, 0, 0, 250, 500);
					wu.plotLine(wu_points, 100, 0, 350, 500);
					createWindowAndRender(bresenham_points, wu_points);
					break;
				case 4:
					bresenham.plotLine(bresenham_points, 1, 500, 80, 1);
					wu.plotLine(wu_points, 100, 500, 180, 1);
					createWindowAndRender(bresenham_points, wu_points);
					break;
				case 5:
					bresenham.plotLine(bresenham_points, 0, 10, 500, 10);
					wu.plotLine(wu_points, 0, 50, 500, 50);
					createWindowAndRender(bresenham_points, wu_points);
					break;
				case 6:
					bresenham.plotLine(bresenham_points, 10, 1, 10, 450);
					wu.plotLine(wu_points, 50, 1, 50, 450);
					createWindowAndRender(bresenham_points, wu_points);
					break;
				default:
					throw std::string("ERROR: Invalid number. Enter 1-6 or 'q' to go back\n");
					break;
				}
			}
			catch (std::string e) {
				std::cout << e << std::endl;
			}
		}
	}
}

void showCustomRenderMenu(BresenhamLine bresenham, XiaolinWuLine wu) {
	std::vector<Point> bresenham_points;
	std::vector<Point> wu_points;
	int x0, y0, x1, y1;

	std::cout << "Enter Bresenham line endpoints  (x0 y0 x1 y1): ";
	try {
		if (!(std::cin >> x0 >> y0 >> x1 >> y1)) {
			throw std::string("\nERROR: Invalid coordinate input, please separate with spaces and use only numbers (e.g. 0 0 600 400)\n");
		}
		else {
			bresenham.plotLine(bresenham_points, x0, y0, x1, y1);
		}
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	std::cout << "Enter Xiaolin Wu line endpoints (x0 y0 x1 y1): ";
	try {
		if (!(std::cin >> x0 >> y0 >> x1 >> y1)) {
			throw std::string("\nERROR: Invalid coordinate input, please separate with spaces and use only numbers (e.g. 0 0 600 400)\n");
		}
		else {
			wu.plotLine(wu_points, x0, y0, x1, y1);
			std::cout << std::endl;
		}
	}
	catch (std::string e) {
		std::cout << e << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		return;
	}

	createWindowAndRender(bresenham_points, wu_points);
}

void showTimeTestsHelp() {
	std::cout << "Enter 'q' to return to the previous menu. Input 'help' to display this menu again.\n\n";
	std::cout << "Enter 'set infile filename.in' to specify a file from tests/ to use.\n";
	std::cout << "Use 'set output false' or 'set output 0' to disable creation of output files.\n";
	std::cout << "Set to true or 1 to re-enable. Disabling output will automatically enable verbose mode.\n";
	std::cout << "Output files will be saved as 'filename_bresenham.out' and 'filename_wu.out'.\n";
	std::cout << "To show timing results on screen, 'set verbose true' or 'set verbose 1'. Disable with false or 0.\n\n";
	std::cout << "To see available files in tests/ enter 'show tests'. Ignore the quotes around file names.\n";
	std::cout << "Use 'show variables' to see values of currently set variables.\n\n";
	std::cout << "Enter 'run' once you are ready to execute the tests." << std::endl;
	std::cout << std::endl;
}

void showTimeTestsMenu(BresenhamLine bresenham, XiaolinWuLine wu) {
	std::string input, testfile = "none";
	bool output = true, verbose = false;
	int bx0, by0, bx1, by1;		// Bresenham endpoints
	int wx0, wy0, wx1, wy1;		// Wu endpoints
	std::vector<Point> bresenham_points;
	std::vector<Point> wu_points;

	std::cout << "*===================================*" << std::endl;
	std::cout << "* Welcome to the time testing area! *" << std::endl;
	std::cout << "*===================================*" << std::endl;
	std::cout << std::endl;

	showTimeTestsHelp();

	while (1) {
		std::cout << "$ test> ";
		std::getline(std::cin, input);
		std::cout << std::endl;

		std::stringstream ss(input);
		std::string token;
		std::vector<std::string> tokens;

		while (ss >> token) {
			tokens.push_back(token);
		}

		if (tokens[0] == "q") {
			return;
		}

		else if (tokens[0] == "help") {
			showTimeTestsHelp();
		}
		
		else if (tokens[0] == "set") {
			if (tokens[1] == "infile") {
				testfile = tokens[2];
			}
			else if (tokens[1] == "output") {
				if (tokens[2] == "true" || tokens[2] == "1") {
					output = true;
				}
				else if (tokens[2] == "false" || tokens[2] == "0") {
					output = false;
					verbose = true;
				}
				else {
					std::cout << "Unknown value for 'output' given. Only use true/false or 1/0." << std::endl;
					continue;
				}
			}
			else if (tokens[1] == "verbose") {
				if (tokens[2] == "true" || tokens[2] == "1") {
					verbose = true;
				}
				else if (tokens[2] == "false" || tokens[2] == "0") {
					verbose = false;
				}
				else {
					std::cout << "Unknown value for 'verbose' given. Only use true/false or 1/0." << std::endl;
					continue;
				}
			}
			else {
				std::cout << "Missing or unkown 'set' variable. Please use 'infile', 'output', or verbose" << std::endl;
				continue;
			}
		}

		else if (tokens[0] == "show") {
			if (tokens[1] == "tests" || tokens[1] == "test") {
				std::string path = "../../../tests/";
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					if (entry.path().filename() != "generate_endpoints.py" && entry.path().filename() != "results") {
						std::cout << entry.path().filename() << std::endl;
					}
				}
				std::cout << std::endl;
				continue;
			}
			else if (tokens[1] == "variables" || tokens[1] == "variable") {
				std::cout << "Current values:" << std::endl;
				std::cout << "---------------" << std::endl;
				std::cout << "  infile: " << testfile << std::endl;
				std::cout << "  output: " << output << std::endl;
				std::cout << "  verbose: " << verbose << std::endl;
				std::cout << std::endl;
			}
		}

		else if (tokens[0] == "run") {
			std::ifstream infile("../../../tests/" + testfile);
			if (!infile.is_open()) {
				std::cout << "Failed to open file -- returning to main menu" << std::endl;;
				return;
			}

			if (verbose == true) {
				std::cout << std::left << std::setw(25) << "Bresenham Time (us):"
					<< std::setw(25) << "Xiaolin Wu Time (us):" << std::endl;
			}
			
			// Strip testfile extension and add _type.out
			std::string obresenham = testfile.substr(0, testfile.find_last_of(".")) + "_bresenham.out";
			std::string owu = testfile.substr(0, testfile.find_last_of(".")) + "_wu.out";
			std::ofstream of_bresenham("../../../tests/results/" + obresenham, std::ios_base::app);
			std::ofstream of_wu("../../../tests/results/" + owu, std::ios_base::app);

			std::string line;
			while (std::getline(infile, line)) {
				std::stringstream ss(line);
				if (!(ss >> bx0 >> by0 >> bx1 >> by1 >> wx0 >> wy0 >> wx1 >> wy1)) {
					std::cout << "Failed to read in coordinates -- check input file for errors" << std::endl;
					return;
				}

				auto startb = std::chrono::high_resolution_clock::now();
				bresenham.plotLine(bresenham_points, bx0, by0, bx1, by1);
				auto endb = std::chrono::high_resolution_clock::now();
				auto timeb = std::chrono::duration_cast<std::chrono::microseconds>(endb - startb);

				auto startw = std::chrono::high_resolution_clock::now();
				wu.plotLine(wu_points, wx0, wy0, wx1, wy1);
				auto endw = std::chrono::high_resolution_clock::now();
				auto timew = std::chrono::duration_cast<std::chrono::microseconds>(endw - startw);

				if (output == true) {
					if (!of_bresenham.is_open() || !of_wu.is_open()) {
						std::cout << "Failed to open files for writing results -- returning to menu...\n" << std::endl;
						return;
					}
					of_bresenham << timeb << std::endl;
					of_wu << timew << std::endl;
				}
				
				if (verbose == true) {
					std::cout << std::left << std::setw(25) << timeb.count()
						<< std::setw(25) << timew.count() << std::endl;
				}
			}
			if (output == true) {
				of_bresenham.close();
				of_wu.close();
			}
		}
		else {
			std::cout << "Not a recognized command. Enter 'help' to read available actions.\n" << std::endl;
			continue;
		}
	}
}