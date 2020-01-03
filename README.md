# Kendall Tau P Value

This repository contains an implementation of the computation of the pvalue of
the Kendall tau correlation coefficient in C++ and Python.

We know that this computation is available in scipy (cf `scipy.stats.kendalltau`).
However, due to our work, we need to modify some part of it.

That is why we are reimplementing it. We use C++ to compute the z-score and python
to compute the pvalue.

This project has only one dependency in C++ : [Pybind11](https://github.com/pybind/pybind11) to bind C++ in Python. However, we loose the dynamic type system using it so
it is limited to some type for the computation of the zscore (see `./src/python/_kt.cc`).
