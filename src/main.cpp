#include "tanagram/ClassFile.h"
#include <iostream>
#include <string>
#include <sstream>
#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(tanagram, m) {
  py::class_<ClassFile>(m, "ClassFile")
    .def(py::init<std::string>())
    .def("hex_dump", &ClassFile::hexDump)
    .def("process_file", &ClassFile::processFile)
    .def("__str__", [](const ClassFile& obj) {
        std::stringstream ss;
        ss << obj;
        return ss.str();
    })
    .def("__repr__", [](const ClassFile& obj) {
        std::stringstream ss;
        ss << obj;
        return ss.str();
    });
}

// END OF FILE
