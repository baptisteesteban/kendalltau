#ifndef Z_SCORE_HH
#define Z_SCORE_HH

#include <kt/histogram.hh>
#include <kt/table.hh>

#include <cmath>

namespace kt
{
  template <typename T>
  float z_score(std::shared_ptr<table<T>> arr1, std::shared_ptr<table<T>> arr2);

  namespace internals
  {
    template <typename T>
    float vx(std::shared_ptr<histogram<T>> x);

    template <typename T>
    float v1(std::shared_ptr<histogram<T>> t, std::shared_ptr<histogram<T>> u,
             std::size_t n);

    template <typename T>
    float v2(std::shared_ptr<histogram<T>> t, std::shared_ptr<histogram<T>> u,
             std::size_t n);

    template <typename T>
    float v(std::shared_ptr<histogram<T>> t, std::shared_ptr<histogram<T>> u,
            std::size_t n);
  } // namespace internals
} // namespace kt

/******************
 * IMPLEMENTATION *
 ******************/

namespace kt
{
  namespace internals
  {
    template <typename T>
    float vx(std::shared_ptr<histogram<T>> x)
    {
      float res = 0;
      for (std::size_t i = 0; i < x->h.size(); i++)
      {
        std::size_t e = x->h[i];
        res += static_cast<float>(e * (e - 1) * (2 * e + 5));
      }
      return res;
    }

    template <typename T>
    float v1(std::shared_ptr<histogram<T>> t, std::shared_ptr<histogram<T>> u,
             std::size_t n)
    {
      std::size_t a = 0;
      std::size_t b = 0;
      for (std::size_t i = 0; i < t->h.size(); i++)
        a += t->h[i] * (t->h[i] - 1);
      for (std::size_t i = 0; i < u->h.size(); i++)
        b += u->h[i] * (u->h[i] - 1);
      return static_cast<float>(a * b) / static_cast<float>(2 * n * (n - 1));
    }

    template <typename T>
    float v2(std::shared_ptr<histogram<T>> t, std::shared_ptr<histogram<T>> u,
             std::size_t n)
    {
      float a = 0;
      float b = 0;
      for (std::size_t i = 0; i < t->h.size(); i++)
        a += t->h[i] * (t->h[i] - 1) * (t->h[i] - 2);
      for (std::size_t i = 0; i < u->h.size(); i++)
        b += static_cast<float>(u->h[i] * (u->h[i] - 1) * (u->h[i] - 2)) /
             static_cast<float>(9 * n * (n - 1) * (n - 2));
      return a * b;
    }

    template <typename T>
    float v(std::shared_ptr<histogram<T>> t, std::shared_ptr<histogram<T>> u,
            std::size_t n)
    {
      float v0 = n * (n - 1) * (2 * n + 5);
      return (v0 - vx(t) - vx(u)) / 18.f + v1(t, u, n) + v2(t, u, n);
    }
  } // namespace internals

  template <typename T>
  float z_score(std::shared_ptr<table<T>> arr1, std::shared_ptr<table<T>> arr2)
  {
    if (arr1->capacity != arr2->capacity)
      throw std::runtime_error(
          "The two input tables should have the same size ");

    std::size_t n = arr1->capacity;
    auto        t = make_histogram(arr1);
    auto        u = make_histogram(arr2);

    int nc = 0;
    int nd = 0;
    for (std::size_t i = 0; i < n; i++)
    {
      for (int j = i - 1; j > -1; j--)
      {
        T xi = arr1->data[i];
        T xj = arr1->data[j];
        T yi = arr2->data[i];
        T yj = arr2->data[j];

        if ((xi > xj && yi > yj) || (xi < xj && yi < yj))  
          nc++;
       

        if ((xi > xj && yi < yj) || (xi < xj && yi > yj))
          nd++;
      }
    }

    return static_cast<float>(nc - nd) / std::sqrt(internals::v(t, u, n));
  }
} // namespace kt

#endif /* !Z_SCORE_HH */
