#ifndef RGB_HH
#define RGB_HH

#include <memory>
#include <ostream>

#include <kt/table.hh>

namespace kt
{
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

  template <typename T>
  bool operator==(const rgb_t<T>& lhs, const rgb_t<T>& rhs);

  template <typename T>
  bool operator<(const rgb_t<T>& lhs, const rgb_t<T>& rhs);

  template <typename T>
  bool operator>(const rgb_t<T>& lhs, const rgb_t<T>& rhs);
} // namespace kt

/******************
 * IMPLEMENTATION *
 ******************/

namespace kt
{
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

  template <typename T>
  bool operator==(const rgb_t<T>& lhs, const rgb_t<T>& rhs)
  {
    return lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b;
  }

  template <typename T>
  bool operator<(const rgb_t<T>& lhs, const rgb_t<T>& rhs)
  {
    if (lhs.r == rhs.r)
    {
      if (lhs.g == rhs.g)
      {
        if (lhs.b < rhs.b)
          return true;
        else
          return false;
      }
      else if (lhs.g < rhs.g)
        return true;
      else
        return false;
    }
    else if (lhs.b < rhs.b)
      return true;
    else
      return false;
  }

  template <typename T>
  bool operator>(const rgb_t<T>& lhs, const rgb_t<T>& rhs)
  {
    if (lhs.r == rhs.r)
    {
      if (lhs.g == rhs.g)
      {
        if (lhs.b > rhs.b)
          return true;
        else
          return false;
      }
      else if (lhs.g > rhs.g)
        return true;
      else
        return false;
    }
    else if (lhs.b > rhs.b)
      return true;
    else
      return false;
  }

} // namespace kt

#endif /* !RGB_HH */
