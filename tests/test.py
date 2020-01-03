#!/usr/bin/env python3

from scipy.stats import kendalltau
from kendall import kendalltau_p_value
import numpy as np

t1 = np.random.randint(256, size=500)
t2 = np.random.randint(256, size=500)

_, p_ref = kendalltau(t1, t2)
p_exp = kendalltau_p_value(t1, t2)

print("p_ref =", p_ref)
print("p_exp =", p_exp)
