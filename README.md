# hARMful [![CircleCI](https://circleci.com/gh/dcarlus/hARMful.svg?style=svg)](https://circleci.com/gh/dcarlus/hARMful) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/5690dc89003b44f6b12456ca512a793d)](https://www.codacy.com/app/dcarlus/hARMful?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=dcarlus/hARMful&amp;utm_campaign=Badge_Grade)
**hARMful** is a project aimed at making a whole experience for programming video games and interactive 2D/3D applications.

More informations on the project can be found [here](https://dcarlus.github.io/hARMful/).

## Repository
The repository is structured in different parts:
-   **Libraries**: the source code of the libraries that compose the project;
-   **Softwares**: some demos to show how to use the libraries and their capabilities;
-   **Tools**: some internal tools developed to help creating the libraries. They are not required to use the library nor to be integrated into the applications;
-   **UnitTests**: unit tests to check that the different classes and modules are working as expected, without regressions. The unit tests use a home-made build system. They are run at each commit through the continuous integration;

## Dependencies
All the libraries require `cmake`.

**Important note:** Windows users do not have to install these dependencies. All of them are automatically downloaded and compiled within the hARMful project, you do not have to install them on your system.

### HOPEful (OpenGL rendering)
-   [GLFW 3.2.1](https://github.com/glfw/glfw) (for window and inputs)
-   [GLEW 2.1.0](https://github.com/nigels-com/glew) (for modern OpenGL functions)
-   [Assimp 4.1.0](https://github.com/assimp/assimp) (for importing 3D file models)

### MINDful (mathematics tools)
-   A "modern" Intel/AMD CPU with, at least, SSE2 support is required
-   SSE4 support is recommanded for improved performances
-   ARM CPUs with NEON are not yet supported

### SPITEful (multimedia files management)
-   [libpng 1.6.35](https://github.com/glennrp/libpng)
-   [libjpeg-turbo 2.0.1](https://github.com/libjpeg-turbo/libjpeg-turbo)

## Source code
The source code of the **hARMful** project is mainly written in C++17 language and SIMD operations.

To compile the code, enter into the Libraries folder and compile all the libraries at once by typing `cmake .`.

### GNU/Linux
A compliant compiler is required, g++ is advised.

Install the dependencies on your system.

To compile on a GNU/Linux system, enter the `Library` folder and type `cmake .` then `make`. It will generate the `.so` files.

### Microsoft® Windows™
The compilation of **hARMful** on Microsoft® Windows™ is still work in progress.

### Mac™ OS
Not officially supported.
