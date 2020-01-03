#!/usr/bin/env python3

from scipy.stats import kendalltau
from kendall import kendalltau_p_value
import numpy as np
from time import time

import sys

if len(sys.argv) < 2:
    raise Exception("Usage: ./test.py N\n\tN: number of element in the random array")

N = int(sys.argv[1])

t1 = np.random.randint(256, size=N)
t2 = np.random.randint(256, size=N)

start = time()
_, p_ref = kendalltau(t1, t2)
end = time()
ref_time = end - start

start = time()
p_exp = kendalltau_p_value(t1, t2)
end = time()
exp_time = end - start

print("p_ref =", p_ref, "in", ref_time, "ms")
print("p_exp =", p_exp, "in", exp_time, "ms")
