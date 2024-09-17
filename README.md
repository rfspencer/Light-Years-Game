# Light Years
An arcade-style spece shooter.

# Build
## Get Source
Clone the source code:

    git clone https://github.com/rfspencer/Light-Years-Game.git

To update an existing clone you can use the colling commands from the root of the project:

    git pull
    git submodule update --init --recursive

You can use [Git for Windows](https://git-for-windows.github.io/) to clone the repository on Windows.

## Dependencies
- The latest version of [CMake](https://cmake.org/) (3.27 or greater)
- Ninja build system
- Libraries will download with CMake

### Windows Dependencies
- Windows 10/11 
- [Visual Studio 2022](https://visualstudio.microsoft.com/downloads/) or [MinGW](https://www.mingw-w64.org/)

## Compiling
1. Create a `build` folder in the project root directory.
        
        cd LightYears
        mkdir build

   If you want to start with a clean build you can simply delete the `build` directory and start again

2. Enter the new directory and execute `cmake`:

       cd build
       cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug

   Cmake will need different flags depending on your platform. You must check the details for
   [Windows](#windows-details), [macOS](#macos-details), and
   [Linux](#linux-details). Some `cmake` options can be modified using tools like
   [`ccmake`](https://cmake.org/cmake/help/latest/manual/ccmake.1.html)
   or [`cmake-gui`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html).

3. After you have executed and configured `cmake`, you have to compile the project:

       cd LightYears\build
       ninja LightYearsGame

4. When `ninja` finishes the compilation, you can find the executable inside the `build\LightYearsGame` folder.

## Alternative Compiling
You can also just [open the project folder in CLion](https://www.jetbrains.com/clion/) and it will just work. Like magic.