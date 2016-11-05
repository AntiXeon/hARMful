# hARMful
**hARMful** is a project aimed at making a whole experience for programming video games and interactive 2D/3D applications.

More informations on the project can be found [here](https://dcarlus.github.io/hARMful/).

## Repository
The repository is structured in different parts:
* **Documentation**: contains all the documentation and specifications on the project and its libraries;
* **Libraries**: the source code of the libraries that compose the project;
* **Softwares**: some demos to show how to use the libraries and their capabilities;
* **Tools**: some internal tools developed to help creating the libraries. They are not required to use the library nor to be integrated into the applications;
* **UnitTests**: unit tests to check that the different classes and modules are working as expected, without regressions. The unit tests use a home-made build system;

## Source code
The source code of the **hARMful** project is mainly written in C++14 language and SIMD operations. A compliant compiler is required, g++ is advised.

At the moment, only GNU/Linux distributions are supported. Microsoft(r) Windows(r) OSes are not intended to be supported for now, even if it might be possible the code compiles on such systems.
