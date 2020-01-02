#ifndef HISTOGRAM_HH
#define HISTOGRAM_HH

#include <memory>
#include <vector>

#include <kt/table.hh>

namespace kt
{
    template <typename T>
    struct histogram
    {
      using value_t = T;
      histogram(const std::size_t n)
        : h(n)
        , keys(n)
      {
      }
      std::vector<std::size_t> h;
      std::vector<value_t>     keys;
    };

    template <typename T>
    std::shared_ptr<histogram<T>> make_histogram(std::shared_ptr<table<T>>);
}

/******************
 * IMPLEMENTATION *
 ******************/

#include <iostream>

namespace kt
{
  template <typename T>
  std::shared_ptr<histogram<T>> make_histogram(std::shared_ptr<table<T>> arr)
  {
    auto unique = std::vector<T>();
    unique.push_back(arr->data[0]);
    for (std::size_t i = 1; i < arr->capacity; i++)
    {
      bool u = true;
      for (std::size_t j = 0; j < unique.size(); j++)
        if (arr->data[i] == unique[j])
          u = false;
      if (u)
        unique.push_back(arr->data[i]);
    }
    auto res = std::make_shared<histogram<T>>(unique.size());

    std::copy(unique.begin(), unique.end(), res->keys.begin());

    for (std::size_t k = 0; k < res->keys.size(); k++)
    {
      for (std::size_t i = 0; i < arr->capacity; i++)
      {
        if (arr->data[i] == res->keys[k])
          res->h[k]++;
      }
    }

    return res;
  }
}

#endif /* !HISTOGRAM_HH */
