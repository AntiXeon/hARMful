# hARMful [![CircleCI](https://circleci.com/gh/dcarlus/hARMful.svg?style=svg)](https://circleci.com/gh/dcarlus/hARMful) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/5690dc89003b44f6b12456ca512a793d)](https://www.codacy.com/app/dcarlus/hARMful?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=dcarlus/hARMful&amp;utm_campaign=Badge_Grade)
**hARMful** is a project aimed at making a whole experience for programming video games and interactive 2D/3D applications.

More informations on the project can be found [here](https://dcarlus.github.io/hARMful/).

## Repository
The repository is structured in different parts:
* **Libraries**: the source code of the libraries that compose the project;
* **Softwares**: some demos to show how to use the libraries and their capabilities;
* **Tools**: some internal tools developed to help creating the libraries. They are not required to use the library nor to be integrated into the applications;
* **UnitTests**: unit tests to check that the different classes and modules are working as expected, without regressions. The unit tests use a home-made build system. They are run at each commit through the continuous integration;

## Dependencies
All the libraries require `cmake`.

### HOPEful (OpenGL rendering)
* GLFW 3.2.1: https://github.com/glfw/glfw (for window and inputs)
* GLEW 2.1.0: https://github.com/nigels-com/glew (for modern OpenGL functions)
* Assimp 4.1.0: https://github.com/assimp/assimp (for importing 3D file models)

### MINDful (mathematics tools)
* Recommended hardware: a "modern" Intel/AMD CPU with, at least, SSE2 support

### SPITEful (multimedia files management)
* libpng 1.6.35: https://github.com/glennrp/libpng
* libjpeg-turbo 2.0.1: https://github.com/libjpeg-turbo/libjpeg-turbo

## Source code
The source code of the **hARMful** project is mainly written in C++14 language and SIMD operations. A compliant compiler is required, g++ is advised.

To compile the code, enter into the Libraries folder and compile all the libraries at once by typing `cmake .`.

### GNU/Linux
Install the dependencies on your system.

To compile on a GNU/Linux system, enter the `Library` folder and type `cmake .` then `make`. It will generate the `.so` files.

### Microsoft® Windows™
Use the command line `git clone https://github.com/dcarlus/hARMful.git --recurse-submodules` to clone the repository and its dependencies.

Enter the `Library` folder. To create a Microsoft® Visual Studio® solution, type `cmake .`. A `.sln` file is generated and can be opened with Microsoft® Visual Studio®. If you do not have this IDE, you can download [Microsoft® Visual Studio® Community](https://www.visualstudio.com/vs/visual-studio-express/) for free.
Once the IDE is launched, compile the project and a `.dll` file is generated with a `.lib` for the linker.

PS: If you want to compile the DLLs using a 64-bit architecture, use the command `cmake -DCMAKE_GENERATOR_PLATFORM=x64 .`

### Mac™ OS
Not officially supported.
