# main-curve_on_torus project

A simple project example showing how to use curve_on_torus from igl_GfCS.

## Download igl_GfCS

The cmake build system will attempt to find igl_GfCS according to environment variables (e.g., `IGL_GfCS`). The first time you try to build the example, you should clone a copy of igl_GfCS inside the directory **above** the example/ directory.

    cd PATH_TO_EXAMPLE/..
    git clone https://github.com/olkido/igl_GfCS.git

## Compile

Compile this project using the standard cmake routine:

    cd PATH_TO_EXAMPLE/
    mkdir build
    cd build
    cmake -DIGL_GfCS="$PWD/../../igl_GfCS" ../
    make

This should find and build the dependencies and create an `example` binary.

### Note for linux users

Many linux distributions do not include gcc and the basic development tools in their default installation. On Ubuntu, you need to install the following packages:

    sudo apt-get install git
    sudo apt-get install build-essential
    sudo apt-get install cmake
    sudo apt-get install libx11-dev
    sudo apt-get install mesa-common-dev libgl1-mesa-dev libglu1-mesa-dev
    sudo apt-get install libxrandr-dev
    sudo apt-get install libxi-dev
    sudo apt-get install libxmu-dev
    sudo apt-get install libblas-dev
    sudo apt-get install libxinerama-dev
    sudo apt-get install libxcursor-dev

## Run

From within the `build` directory just issue:

    ./example r R a1 a2 N p0_x p0_y

where r, R, a1, a2, N, p0_x, p0_y are the parameters used in igl::curve_on_torus. If less parameters are provided then defaults are used (see main.cpp) A viewer window should launch displaying a torus mesh and the curve on it.
