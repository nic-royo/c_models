# Minimum required CMake version
cmake_minimum_required(VERSION 3.12)

# Project name
project(c_models)

set(CMAKE_CXX_STANDARD 11)

# # Place exectubales and libraries in the build directory
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find the Armadillo library
find_package(Armadillo REQUIRED)
include_directories(${ARMADILLO_INCLUDE_DIRS})

# Find the MLPack library
find_package(MLPACK REQUIRED)

# Add source files
add_executable(data_split src/c_data_splitter.cpp)
add_executable(random_forest src/random_forest.cpp)
add_executable(ada_boost src/ada_boost.cpp)
add_executable(knn src/knn.cpp)


# Link the libraries to your executable
target_link_libraries(data_split ${MLPACK_LIBRARIES} ${ARMADILLO_LIBRARIES})


