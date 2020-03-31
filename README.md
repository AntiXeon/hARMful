![hARMful banner](./docs/assets/images/logo/hARMful_Preview.png)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/5690dc89003b44f6b12456ca512a793d)](https://www.codacy.com/app/dcarlus/hARMful?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=dcarlus/hARMful&amp;utm_campaign=Badge_Grade)

**hARMful** is a project aimed at making a whole experience for programming video games and interactive 2D/3D applications.

> Learn more and read the documentation on [https://dcarlus.github.io/hARMful/](https://dcarlus.github.io/hARMful/).

## Repository
The repository is structured in different parts:
-   **Libraries**: the source code of the libraries that compose the project;
-   **Softwares**: some demos to show how to use the libraries and their capabilities;
-   **Tools**: some internal tools developed to help creating the libraries. They are not required to use the library nor to be integrated into the applications;
-   **UnitTests**: unit tests to check that the different classes and modules are working as expected, without regressions. The unit tests use a home-made build system. They are run at each commit through the continuous integration;

## Dependencies
### HOPEful (OpenGL rendering)
-   [GLFW 3.2.1](https://github.com/glfw/glfw) (for window and inputs)
-   [GLEW 2.1.0](https://github.com/nigels-com/glew) (for modern OpenGL functions)
-   [Assimp 5.1.0](https://github.com/assimp/assimp) (for importing 3D file models)
-   Hardware supporting OpenGL 4.5 or higher is required

### MINDful (mathematics tools)
-   A "modern" Intel/AMD CPU with, at least, SSE2 support is required
-   SSE4 support is recommanded for improved performances
-   ARM CPUs with NEON are not yet supported

### SPITEful (multimedia files management)
-   [libpng 1.6.37](https://github.com/glennrp/libpng)
-   [libjpeg-turbo 2.0.2](https://github.com/libjpeg-turbo/libjpeg-turbo)

## Compilation
### GNU/Linux
The compilation process for GNU/Linux users is shown in this video : https://www.youtube.com/watch?v=zECjVr_6qko

#### Requirements
- CMake 2.8.12 or above;
- A C++17 compliant compiler is required, `g++9` and above is advised.

#### Optional tools
- Conan (you can install conan with your package manager or using `pip`).

#### Build steps
Install the requirements on your system.

:exclamation: You can either choose to install the dependencies from your distribution package manager, or let Conan select the right libraries from its own repository. Just build the project and CMake will select the right ones according to what is installed on your system.

To compile on a GNU/Linux system, enter the `Library` folder and type `./build.sh` in a command prompt. It will generate the `.so` files.

### Microsoft® Windows™
The compilation process for Windows users is shown in this video: https://www.youtube.com/watch?v=W5kpHneNB9I

#### Requirements
- [CMake 2.8.12](https://cmake.org/download/) or above (add CMake to the `PATH` environment variable);
- [Visual Studio 2019](https://visualstudio.microsoft.com) and above. Notice that Visual Studio Community is free to use. **Previous versions of Visual Studio cannot build the project!**
- [Conan](https://conan.io/downloads.html)
    - If you have troubles using Conan, you can install it with `pip` (Python 3). Think to add Python to the `PATH` environment variable then install Conan by typing the `pip install conan` command.

#### Build steps
- Install all the requirements.
- Open the CMake GUI:
    - Select the **hARMful** `Tools\GLSL2Cpp\build` directory for both "source code" and "build" folders.
    - Press the "Configure" button, no matter the compiler you use. Select either the Win32 or x64 configuration.
    - Press the "Generate" button then open the `GLSL2Cpp.sln` file with Visual Studio. Build the tool, no matter it is in debug or release mode.
    - Quit Visual Studio once it's done then launch the `Tools\GLSL2Cpp\bin\**\glsl2cpp.exe` file where you provide the path to the **hARMful** root directory. It will ask for administrator rights to create the shortcut to the HOPEful library directory, so accept the request. The `glsl2cpp` tool copies the content of the embedded GLSL shaders into C++ files (hpp/cpp), in order to embed the shaders inside the DLL itself. That's all!
- Come back to the **hARMful** home directory.
- Open the CMake GUI:
    - Select the **hARMful** `Library` directory for both "source code" and "build" folders.
    - Press the "Configure" button, check that Visual Studio 2019 is selected and use the `x64` platform in combobox. Press "Finish" when it's done. Wait until the configuration is complete (it can take a while if the dependencies have to be downloaded by Conan).
    - Press the "Generate" button then close CMake.
- Open the generated `hARMful.sln` file with Visual Studio 2019. Compile the projects in either Release or Debug mode.
- The DLLs are built in their library directories.
- Notice that you have to copy the dependencies for SPITE and HOPE from the `.conan` directory (look into your user directory) to run your hARMful-based applications.

### Mac™ OS
Not officially supported.
