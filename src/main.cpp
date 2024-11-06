#include <pybind11/pybind11.h>
#include <iostream>

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

void loseIt() {
	std::cout << "NOOOOOO this cannot be happening!!1!" << std::endl;
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

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
