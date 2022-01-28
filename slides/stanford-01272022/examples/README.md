# Example Code

## Build Instructions

First run:
```
./setup.sh
```
This will install the dependencies for all the example code inside a folder called `libs`.
The dependencies are:
- [Eigen-3.3.9](https://eigen.tuxfamily.org/index.php?title=Main_Page)
- [FastAD](https://github.com/JamesYang007/FastAD)

You will also need to install CMake.
Follow the download instructions [here](https://cmake.org/install/).

Once the dependencies have been installed, 
run the following command to build the example code:
```
./clean-build.sh
```
This will create executables stored in `build/src`.
