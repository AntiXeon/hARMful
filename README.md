# hARMful [![CircleCI](https://circleci.com/gh/dcarlus/hARMful/tree/master.svg?style=svg)](https://circleci.com/gh/dcarlus/hARMful/tree/master)
**hARMful** is a project aimed at making a whole experience for programming video games and interactive 2D/3D applications.

More informations on the project can be found [here](https://dcarlus.github.io/hARMful/).

## Repository
The repository is structured in different parts:
* **Libraries**: the source code of the libraries that compose the project;
* **Softwares**: some demos to show how to use the libraries and their capabilities;
* **Tools**: some internal tools developed to help creating the libraries. They are not required to use the library nor to be integrated into the applications;
* **UnitTests**: unit tests to check that the different classes and modules are working as expected, without regressions. The unit tests use a home-made build system;

## Dependencies
All the libraries require `cmake`.

### DOOMful
* GLFW 3.2.1: https://github.com/glfw/glfw
* GLEW 2.0.0: https://github.com/nigels-com/glew

## Source code
The source code of the **hARMful** project is mainly written in C++14 language and SIMD operations. A compliant compiler is required, g++ is advised.

To compile the code, enter into the Libraries folder and compile all the libraries at once by typing `cmake .`.

### GNU/Linux
To compile on a GNU/Linux system, type `cmake .` then `make`. It will generate the `.so` file.

### Microsoft® Windows™
To create a Microsoft® Visual Studio® solution, type `cmake .`. A `.sln` file is generated and can be opened with Microsoft® Visual Studio®. If you do not have this IDE, you can download [Microsoft® Visual Studio® Express](https://www.visualstudio.com/vs/visual-studio-express/) for free.
Once the IDE is launched, compile the project and a `.dll` file is generated.

### Mac™ OS
Not officially supported.
