# CSCI 411 | Line Drawing Algorithms

## Setup

This project uses CMake to handle building. It should automatically install SDL3 before compiling. The code assumes builds are located in `out/build/`. The program has been tested on Windows and Debian.

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
### Linux Build Instructions (Debian-based)
1. Clone the repository to the desired location and navigate to it:
	```bash
	git clone https://github.com/leszakal/line-drawing.git
	cd line-drawing
	```
2. Ensure your system has the necessary compiler packages available. The following should get everything necessary:
	```bash
	sudo apt install build-essential
	```
3. Install Ninja with:
	```bash
	sudo apt install ninja-build
	``` 
   Alternatively, create the necessary directory manually:
	```bash
	mkdir -p out/build/linux-debug
	```
4. If you installed Ninja build by running:
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

### MacOS Build Instructions

**Note:** As I do not have access to a Mac device to test the setup the following are estimated instructions created with the help of ChatGPT.

1.  Clone the repository to the desired location and navigate to it:
	```bash
	git clone https://github.com/leszakal/line-drawing.git
	cd line-drawing
	```
2. Install the necessary developer tools with:
	```bash
	xcode-select --install
	```
   You may also be able to set up `gcc` and related packages via Homebrew.
3. Install Ninja with:
	```bash
	brew install ninja
	```
   Or make the directory manually with: 
	```bash
	mkdir -p out/build/macos-debug
	```
4. If you installed Ninja build by running:
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
If you need to run this on a system without a GUI, you add the `-DSDL_UNIX_CONSOLE_BUILD=ON` option to the initial CMake command like so: `cmake --preset linux-debug -DSDL_UNIX_CONSOLE_BUILD=ON`. Only the timed testing option will work in this case.