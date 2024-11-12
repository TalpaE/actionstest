#include <pybind11/pybind11.h>
#include <iostream>
#include <omp.h>
#include <boost/math/special_functions/binomial.hpp>
#include <xc.h>

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

int binomial(int n, int k) {
    return boost::math::binomial_coefficient<double>(n, k);
}

void libxcversion() {
    std::cout << "libxc version: " << xc_version_string() << std::endl;
}

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
    m.def("binomial", &binomial, R"pbdoc(
        Calculate the binomial coefficient

        Returns the binomial coefficient of n and k.
    )pbdoc");
    m.def("libxcversion", &libxcversion, R"pbdoc(
        Print the libxc version

        Prints the version of libxc.
    )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
