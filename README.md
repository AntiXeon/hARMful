# hARMful [![CircleCI](https://circleci.com/gh/dcarlus/hARMful.svg?style=svg)](https://circleci.com/gh/dcarlus/hARMful)
**hARMful** is a project aimed at making a whole experience for programming video games and interactive 2D/3D applications.

More informations on the project can be found [here](https://AntiXeon.github.io/hARMful/).

## Repository
The repository is structured in different parts:
* **Libraries**: the source code of the libraries that compose the project;
* **Softwares**: some demos to show how to use the libraries and their capabilities;
* **Tools**: some internal tools developed to help creating the libraries. They are not required to use the library nor to be integrated into the applications;
* **UnitTests**: unit tests to check that the different classes and modules are working as expected, without regressions. The unit tests use a home-made build system. They are run at each commit through the continuous integration;

## Dependencies
All the libraries require `cmake`.

### HOPEful
* GLFW 3.2.1: https://github.com/glfw/glfw
* GLEW 2.0.0: https://github.com/nigels-com/glew

### MINDful
* Recommended hardware: a "modern" Intel/AMD CPU with, at least, SSE2 support

## Source code
The source code of the **hARMful** project is mainly written in C++14 language and SIMD operations. A compliant compiler is required, g++ is advised.

To compile the code, enter into the Libraries folder and compile all the libraries at once by typing `cmake .`.

### GNU/Linux
To compile on a GNU/Linux system, type `cmake .` then `make`. It will generate the `.so` file.

### Microsoft® Windows™
To create a Microsoft® Visual Studio® solution, type `cmake .`. A `.sln` file is generated and can be opened with Microsoft® Visual Studio®. If you do not have this IDE, you can download [Microsoft® Visual Studio® Community](https://www.visualstudio.com/vs/visual-studio-express/) for free.
Once the IDE is launched, compile the project and a `.dll` file is generated with a `.lib` for the linker.

PS: If you want to compile the DLLs using a 64-bit architecture, use the command `cmake -DCMAKE_GENERATOR_PLATFORM=x64 .`

### Mac™ OS
Not officially supported.
