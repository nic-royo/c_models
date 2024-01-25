# Project Information
Data preprocessing and implementation of RF, AB, and KNN algorithms in C++ using the MLPack library.


## Dependencies
sudo apt-get install libmlpack-dev
sudo apt-get install libarmadillo-dev

## Dependencies
To work with this project, you need to install `mlpack` and `Armadillo`. Install via the following commands:

```bash
sudo apt-get install libmlpack-dev
sudo apt-get install libarmadillo-dev
```
## Compilation and Installation with CMake
To build using CMake, on terminal do:
1. Create a Build directory 
```bash
mkdir build && cd build
```

2. Configure the project with CMake
```bash
cmake .. 
```

3. Build project
```bash
make
```

4. Run the executable
Replace 'executable_name' with the actual name of the built executable (refer to CMakeLists.txt for the executable names, such as data_preprocessing).
```bash
./random_forest
```


## Compilation and Installation without CMake, not recommended once the project becomes bigger
Use the following to compile:
```bash
g++ -o <executable_name> <source_file.cpp> -larmadillo -lmlpack
```

Replace <executable_name> with the wanted output file name, and <source_file.cpp> with the C++ source file you want to compile (such as data_preprocessing src/c_data_splitter.cpp). Link necessary libraries using -l.

## Structure
* CMakeLists.txt: Contains CMake configuration and build settings. Note that CMakeLists.txt has executable source files in format add_executable(<executable_name> <source_file.cpp>)
    * When working with multiple executables or changing the source files, remember to update the names in the compilation commands and CMakeLists.txt accordingly.
* src/: Source files for the project.
* include/: Header files, if any, for future use when making a library instead of indedependent executables

