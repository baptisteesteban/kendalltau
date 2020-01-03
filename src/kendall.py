import numpy as np
from scipy.stats import norm
from _kt import z_score

def kendalltau_p_value(arr1, arr2):
    arr1, arr2 = np.array(arr1), np.array(arr2)
    z = z_score(arr1, arr2)
    return 2 - 2 * norm.cdf(np.abs(z))
