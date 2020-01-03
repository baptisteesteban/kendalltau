#ifndef Z_SCORE_HH
#define Z_SCORE_HH

#include <kt/histogram.hh>
#include <kt/table.hh>

namespace kt
{
  template <typename T>
  float z_score(std::shared_ptr<table<T>> arr1, std::shared_ptr<table<T>> arr2);

  namespace internals
  {
    template <typename T>
    std::size_t vx(std::shared_ptr<histogram<T>> x);

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
    std::size_t vx(std::shared_ptr<histogram<T>> x)
    {
      std::size_t res = 0;
      for (std::size_t i = 0; i < x->h.size(); i++)
      {
        T e = x->h[i];
        res += e * (e - 1) * (2 * e + 5);
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
      return (v0 - vx(t) - vx(u)) / 18 + v1(t, u, n) + v2(t, u, n);
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

    std::size_t nc = 0;
    std::size_t nd = 0;
    for (std::size_t i = 0; i < n; i++)
    {
      for (std::size_t j = i - 1; j > -1; j--)
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

    return (nc - nd) / std::sqrt(internals::v(t, u, n));
  }
} // namespace kt

#endif /* !Z_SCORE_HH */
