# OpenGL inliner
This program is intended to automatically generate C++ inline versions of OpenGL3 functions.

It is not (yet) a C++14 code as it directly handles pointers from the underlying C API of OpenGL. This evolution will be provided once the HOPEful engine development will be initiated.

## How it works
Just run the `convert.sh` script. It will compile the converter program and process the `.gl` files. Moreover, the solution is automatically cleared once the conversion is done.
You will just have to go into the output folder to get all the generated files.

Notice that the converter program itself is coded with the C++98 specifications for a higher compatibilty.

## Releases
|Version|Date      | What's new?                                                       |
|-------|----------|-------------------------------------------------------------------|
|1.0    |2016/10/31| First release. Output C++98 files of the OpenGL3.3 API.           |
