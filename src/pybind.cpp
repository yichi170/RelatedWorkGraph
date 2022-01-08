#include "node.hpp"
#include "system.hpp"
#include <chrono>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
// #include <pybind11/operators.h>

#define fs first
#define sc second

namespace py = pybind11;

PYBIND11_MODULE(nodepy, m) {

	m.doc() = "Python Library for drawing the Related Work Graph of paper";

	py::class_<NodeSystem>(m, "NodeSystem")
		.def(py::init<
			 const int &, const int &, const int &, 
			 const double &, 
			 const std::vector< std::pair<int, int> > &&
			 >(), py::return_value_policy::move)

		.def("run", &NodeSystem::run)

		.def("run_times", &NodeSystem::run_times)
		
		.def("getPos", &NodeSystem::getVector)
		;
}