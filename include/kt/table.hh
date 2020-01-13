#ifndef TABLE_HH
#define TABLE_HH

#include <algorithm>
#include <initializer_list>
#include <memory>
#include <stdexcept>

#include <pybind11/numpy.h>

namespace kt
{
  template <typename T>
  struct table
  {
    table(const std::size_t, const std::size_t);
    std::unique_ptr<T[]> data;
    const std::size_t    capacity; /* Number of value of type T */
    const std::size_t    nb_elem;  /* Number of value by value */
  };

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const table<T>& t);

  template <typename T>
  struct rgb_t
  {
    rgb_t(T cr = 0, T cg = 0, T cb = 0)
      : r(cr)
      , g(cg)
      , b(cb)
    {
    }

    T r;
    T g;
    T b;
  };

  template <typename T>
  std::ostream& operator<<(std::ostream& out, const rgb_t<T>&);

  template <typename T>
  std::shared_ptr<table<rgb_t<T>>> uni_to_multi(std::shared_ptr<table<T>>);

  namespace python
  {
    namespace py = pybind11;

    template <typename T>
    std::shared_ptr<table<T>> from_numpy(const py::array_t<T>&);
  } // namespace python
} // namespace kt

/******************
 * IMPLEMENTATION *
 ******************/

namespace kt
{
  template <typename T>
  table<T>::table(const std::size_t capacity_c, const std::size_t n)
    : data(std::make_unique<T[]>(capacity_c))
    , capacity(capacity_c)
    , nb_elem(n)
  {
    if (capacity_c % n != 0)
      throw std::runtime_error(
          "capacity should be able to contain all the element");
  }

  template <typename T>
  std::ostream& operator<<(std::ostream& out, std::shared_ptr<table<T>> t)
  {
    out << "[";
    for (std::size_t i = 0; i < t->capacity - 1; i++)
      out << t->data[i] << " ";
    out << t->data[t->capacity - 1] << "]\n";
    return out;
  }


  template <typename T>
  std::ostream& operator<<(std::ostream& out, const rgb_t<T>& c)
  {
    out << "(" << c.r << ", " << c.g << ", " << c.b << ")";
    return out;
  }

  template <typename T>
  std::shared_ptr<table<rgb_t<T>>> uni_to_multi(std::shared_ptr<table<T>> t)
  {
    auto res = std::make_shared<table<rgb_t<T>>>(t->capacity / t->nb_elem, 1);
    for (std::size_t i = 0; i < res->capacity; i++)
    {
      res->data[i].r = t->data[i * 3];
      res->data[i].g = t->data[i * 3 + 1];
      res->data[i].b = t->data[i * 3 + 2];
    }
    return res;
  }

  namespace python
  {
    namespace py = pybind11;

    template <typename T>
    std::shared_ptr<table<T>> from_numpy(const py::array_t<T>& arr)
    {
      // Buffer info from python
      auto r = arr.request();

      std::size_t n_elem = 0;
      if (r.ndim == 1)
        n_elem = 1;
      else if (r.ndim == 2 && r.shape[1] == 3)
        n_elem = 3;
      else
        throw std::runtime_error("Bad shapes");

      auto res = std::make_shared<table<T>>(r.shape[0] * n_elem, n_elem);

      for (std::size_t i = 0; i < res->capacity; i++)
        res->data[i] = *(static_cast<T*>(r.ptr) + i);

      return res;
    }
  } // namespace python
} // namespace kt

#endif /* !TABLE_HH */
