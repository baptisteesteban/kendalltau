#include <pybind11/pybind11.h>

#include <kt/z_score.hh>

#include <iostream>

namespace kt
{
    namespace python
    {
      namespace py = pybind11;

      template <typename T>
      float z_score_python(py::array_t<T> arr1, py::array_t<T> arr2)
      {
        auto tab1 = from_numpy(arr1);
        auto tab2 = from_numpy(arr2);
        return z_score(tab1, tab2);
      }

      PYBIND11_MODULE(_kt, m) { m.def("z_score", &z_score_python<int>); }
    }
}
