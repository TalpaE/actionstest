#include <pybind11/pybind11.h>
#include <iostream>
#include <omp.h>
#ifdef USEBOOST
#include <boost/math/special_functions/binomial.hpp>
#endif
#include <xc.h>
#ifdef USEHDF5
#include <H5Cpp.h>
#include <hdf5.h>
#endif

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

void loseIt() {
	std::cout << "NOOOOOO this cannot be happening!!1!" << std::endl;
}

int maxThreads() {
    return omp_get_max_threads();
}

#ifdef USEBOOST
int binomial(int n, int k) {
    return boost::math::binomial_coefficient<double>(n, k);
}
#endif

void libxcversion() {
    std::cout << "libxc version: " << xc_version_string() << std::endl;
}

#ifdef USEHDF5
void writeH5File(std::string name) {
    H5::H5File file("aCoolFile.h5", H5F_ACC_TRUNC);
}
#endif

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: example_package_JonSnowPatrol

        .. autosummary::
           :toctree: _generate

           add
           subtract
           loseIt
           maxThreads
           binomial
           libxcversion
           writeH5File
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");
    m.def("loseIt", &loseIt, R"pbdoc(
        Just lose it

        For rare use only.
    )pbdoc");
    m.def("maxThreads", &maxThreads, R"pbdoc(
        Get the maximum number of threads

        Returns the maximum number of threads that can be used.
    )pbdoc");
    #ifdef USEBOOST
    m.def("binomial", &binomial, R"pbdoc(
        Calculate the binomial coefficient

        Returns the binomial coefficient of n and k.
    )pbdoc");
    #endif
    m.def("libxcversion", &libxcversion, R"pbdoc(
        Print the libxc version

        Prints the version of libxc.
    )pbdoc");
    #ifdef USEHDF5
    m.def("writeH5File", &writeH5File, R"pbdoc(
        Write an HDF5 file

        Writes an HDF5 file with a single number.
    )pbdoc");
    #endif

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
