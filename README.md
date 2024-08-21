# OpenGL study Repository

This repository contains a few programs and a library that I am using to study
OpenGL. Due to the purpose of learning I am implementing my own abstraction
layer over OpenGL and SDL2 to make them more "modern" in C++ sense.

Library can be found in the `/lib` directory and examples can be found in `/src`
directory.

## Build instructions and Usage

I am using conan package manager for managing of my dependencies, thus the first
step is to download them:
```bash
conan install conanfile.py --build=missing -s build_type=Debug
```
As the whole project is still under heavy development we will prefer Debug
build, as we want the additional information in our binaries.

Then we can use the generated CMake preset to create needed build files:
```bash
export conan_toolchain=build/Debug/generators/conan_toolchain.cmake
cmake -Bbuild -DCMAKE_TOOLCHAIN_FILE=$conan_toolchain -DCMAKE_BUILD_TYPE=Debug -GNinja .
```
After that we can safely build the project:
```bash
cmake --build build
```
Compiled examples can be then found in `build/examples`.

For example resulting application `mesh_with_indices` looks like this:

![Mesh with indices example](https://github.com/DanielKriz/opengl-study/blob/master/docs/img/mesh_with_indices.png)

## Acknowledgement
As my linear algebra library is still under development (it can be found [here](https://github.com/DanielKriz/lingebra))
I am facilitating a library developed by the authors of [OpenGL SuperBible](http://www.openglsuperbible.com/).
