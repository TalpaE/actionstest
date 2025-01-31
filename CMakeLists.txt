# Require CMake 3.15+ (matching scikit-build-core) Use new versions of all
# policies up to CMake 3.30
cmake_minimum_required(VERSION 3.15...3.29)

# Scikit-build-core sets these values for you, or you can just hard-code the
# name and version.
project(
  ${SKBUILD_PROJECT_NAME}
  VERSION ${SKBUILD_PROJECT_VERSION}
  LANGUAGES CXX)

set(CMAKE_MODULE_PATH  ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

# Find the module development requirements (requires FindPython from 3.17 or
# scikit-build-core's built-in backport)
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG REQUIRED)

option(USEBOOST "Use Boost" ON)
if (USEBOOST)
# Boost
message("-----Checking Boost-----")
if (CMP0167)
  cmake_policy(SET CMP0167 OLD)
  # use CMake's FindBoost.cmake instead of a configure file by boost (only available from Boost 1.70 onwards)
  set(Boost_NO_BOOST_CMAKE ON)
endif()
find_package(Boost REQUIRED)
endif()

# OpenMP
message("-----Checking OpenMP-----")
find_package(OpenMP REQUIRED)

option(USEHDF5 "Use HDF5" ON)
if (USEHDF5)
  message("-----Checking HDF5-----")
  include(CMakePrintHelpers)
  cmake_print_variables(HDF5_INCLUDE_DIRS HDF5_LIBRARIES HDF5_ROOT)
  set(HDF5_NO_FIND_PACKAGE_CONFIG_FILE TRUE)
  set(HDF5_FIND_DEBUG TRUE)
  find_package(HDF5 REQUIRED COMPONENTS HL CXX)
endif()

# Add a library using FindPython's tooling (pybind11 also provides a helper like
# this)
pybind11_add_module(_core MODULE OPT_SIZE src/main.cpp)
if (USEBOOST)
  target_compile_definitions(_core PRIVATE USEBOOST)
  target_link_libraries(_core PUBLIC pybind11::headers OpenMP::OpenMP_CXX Boost::boost $<$<BOOL:${USEHDF5}>:-hdf5_cpp-shared>)
else()
  target_link_libraries(_core PUBLIC pybind11::headers OpenMP::OpenMP_CXX $<$<BOOL:${USEHDF5}>:-hdf5_cpp-shared>)
endif()

# this looks inside the cmake directory for the ImportLibxc.cmake file
include(ImportLibxc)
import_libxc()
target_link_libraries(_core PRIVATE xc)

# This is passing in the version as a define just as an example
target_compile_definitions(_core PRIVATE VERSION_INFO=${PROJECT_VERSION})

# The install directory is the output (wheel) directory
install(TARGETS _core DESTINATION example_package_JonSnowPatrol)
message(STATUS "finished with the cmake step")