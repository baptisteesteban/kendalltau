#include <pybind11/pybind11.h>

#include <kt/z_score.hh>

#include <cstddef>

#define BIND(T) m.def("z_score", &z_score_python<T>)

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

    PYBIND11_MODULE(_kt, m)
    {
      BIND(int);
      BIND(float);
      BIND(double);
      BIND(unsigned);
      BIND(std::uint8_t);
      BIND(std::uint16_t);
      BIND(std::uint32_t);
      BIND(std::uint64_t);
      BIND(std::int8_t);
      BIND(std::int16_t);
      BIND(std::int32_t);
      BIND(std::int64_t);
    }
  } // namespace python
} // namespace kt
