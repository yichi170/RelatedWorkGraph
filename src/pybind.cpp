#include "node.hpp"
#include "system.hpp"
#include <chrono>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// #include <pybind11/operators.h>

#define fs first
#define sc second

namespace py = pybind11;

PYBIND11_MODULE(system, m) {
	py::class_<NodeSystem>(m, "NodeSystem")
		.def(py::init<
			 const std::vector<std::vector<int>> &, 
			 int, int, int, double, int
			 >())
		// .def("setparam", )
		;
}