#include <pybind11/pybind11.h>

#include <kt/rgb.hh>
#include <kt/z_score.hh>

#include <cstddef>

#define BIND(T) m.def("z_score", &z_score_python<T>)
#define BIND_RGB(T) m.def("rgb_z_score", &rgb_z_score_python<T>);

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

    template <typename T>
    float rgb_z_score_python(py::array_t<T> arr1, py::array_t<T> arr2)
    {
      auto tab1     = from_numpy(arr1);
      auto tab2     = from_numpy(arr2);
      auto tab1_rgb = uni_to_multi(tab1);
      auto tab2_rgb = uni_to_multi(tab2);
      return z_score(tab1_rgb, tab2_rgb);
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

      BIND_RGB(int);
      BIND_RGB(float);
      BIND_RGB(double);
      BIND_RGB(unsigned);
      BIND_RGB(std::uint8_t);
      BIND_RGB(std::uint16_t);
      BIND_RGB(std::uint32_t);
      BIND_RGB(std::uint64_t);
      BIND_RGB(std::int8_t);
      BIND_RGB(std::int16_t);
      BIND_RGB(std::int32_t);
      BIND_RGB(std::int64_t);
    }
  } // namespace python
} // namespace kt
