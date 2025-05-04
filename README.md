# CSCI 411 | Line Drawing Algorithms

This repository holds the code for a CSCI 411 algorithms project. This project examines and implements two line drawing algorithms: Bresenham's and Xiaolin Wu's.

The `src/` directory holds all `.cpp` files. Header files can be found in `include/`.
Test input files and the script used to generate them (`generate_endpoints.py`) are located in `tests/`. Results for the timed testing can found in `tests/results/`. 

The `assets/` directory just holds images used in this README. 

## Setup

This project uses CMake to handle building. It should automatically install SDL3 before compiling. The code assumes builds are located in `out/build/{$presetName}/`. The program has been tested on Windows and Debian.
___
### Windows Build Instructions
1. Install [Visual Studio](https://visualstudio.microsoft.com/)
2. Clone the repository to the desired location:
	```bash
	git clone https://github.com/leszakal/line-drawing.git
	```
3. Open Visual Studio, choose "Open a local folder" and select the repository folder `line-drawing`.
4. Wait for Visual Studio to recognize the CMake configuration -- this may take a few minutes.
5. The program will be ready to run once the start button near the top has changed to read `algo_project.exe`. Click it to run the program:

	![Screenshot of the Visual Studio button to run a program, it reads algo_project.exe](/assets/vs_button_ready.png)
___
### Linux Build Instructions (Debian-based)
1. Clone the repository to the desired location and navigate to it:
	```bash
	git clone https://github.com/leszakal/line-drawing.git
	cd line-drawing
	```
2. Ensure your system has CMake and the necessary compiler packages available. The following should get everything necessary:
	```bash
	sudo apt install build-essential cmake
	```
3. Install Ninja with:
	```bash
	sudo apt install ninja-build
	``` 
   Alternatively, create the necessary directory manually:
	```bash
	mkdir -p out/build/linux-debug
	```
4. If you installed Ninja, build by running:
	```bash
	cmake --preset linux-debug
	cmake --build out/build/linux-debug
	```

   Otherwise run:
	```bash
	cd out/build/linux-debug
	cmake ../../../
	cmake --build .
	```
5. Once built, the program will be located in `/out/build/linux-debug`. Change directories if needed and run:
	```bash
	cd out/build/linux-debug
	./algo_project
	```
___
### MacOS Build Instructions

**Note:** As I do not have access to a Mac device to test the setup the following are estimated instructions created with the help of ChatGPT.

1.  Clone the repository to the desired location and navigate to it:
	```bash
	git clone https://github.com/leszakal/line-drawing.git
	cd line-drawing
	```
2. Install the CMake and the necessary developer tools with:
	```bash
	brew install cmake
	xcode-select --install
	```
   You may also be able to set up `gcc` and related packages via Homebrew.
3. Install Ninja with:
	```bash
	brew install ninja
	```
   Or make the directory manually: 
	```bash
	mkdir -p out/build/macos-debug
	```
4. If you installed Ninja, build by running:
	```bash
	cmake --preset macos-debug
	cmake --build out/build/macos-debug
	```

   Otherwise run:
	```bash
	cd out/build/macos-debug
	cmake ../../../
	cmake --build .
	```
5. Once built, the program will be located in `/out/build/macos-debug`. Change directories if needed and run:
	```bash
	cd out/build/macos-debug
	./algo_project
	```
### Building without a GUI
If you need to run this on a system without a GUI, add the `-DSDL_UNIX_CONSOLE_BUILD=ON` option to the initial CMake command like so: `cmake --preset linux-debug -DSDL_UNIX_CONSOLE_BUILD=ON`. Only the timed testing option will work in this case.

### Alternatives to CMake
If CMake doesn't work, you'll need to set up SDL3 yourself. See this [installation guide](https://github.com/libsdl-org/SDL/blob/main/INSTALL.md) for help. There's also additional platform-specific info here: https://github.com/libsdl-org/SDL/tree/main/docs.

## Usage

The program has several menus which should be fairly straightforward to use. For further guidance, please consult the following example screenshots:

### Example 1: Rendering Lines from Presets

Selecting option 1 in the main menu will allow you to render some preset lines. Once you make a choice of which type to render, a window should open to display them:

![A terminal showing the program's menu. It displays inputs and outputs for the "Render preset lines" option. Below the text is a window showing the rendered lines.](/assets/presets.png)

### Example 2: Rendering Lines from Custom Endpoints

Selecting option 2 will prompt you to enter in start and endpoints for a Bresenham-style line and a Xiaolin Wu-style line. For clarity on input format, if `(x0, y0) = (0, 0)` and `(x1, y1) = (1000, 500)` then the input for that line should be `0 0 1000 500` These line will be rendered on the same screen, so be careful of unintentional overlap.'

![A terminal showing the program's menu. It displays inputs and outputs for the "Render lines from custom endpoints" option. Below the text is a window showing the rendered lines.](/assets/custom.png)

### Example 3: Timed Tests

Selecting option 3 will put you into testing mode. This mode does not render out any lines -- it only times the calculation of pixel information by each algorithm. Input is done through files in the `tests/` directory. Times recorded in microseconds. The menu instructions will give a detailed breakdown of the expected usage.

In this example, the `positive.in` file is used. Output is disabled so no information is saved to files:

![A terminal showing the program's menu. It displays inputs and outputs for the "Run timed tests" option. Results for each algorithm in microseconds are to the screen.](/assets/timed_tests.png)