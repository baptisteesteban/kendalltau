import numpy as np
from scipy.stats import norm
from _kt import z_score, rgb_z_score

def kendalltau_p_value(arr1, arr2):
    arr1, arr2 = np.array(arr1), np.array(arr2)
    if arr1.ndim != arr2.ndim:
        raise Exception("The two array must have the same size")

    z = 0.0
    if arr1.ndim == 1:
        z = z_score(arr1, arr2)
    elif arr1.ndim == 2 and arr1.shape[1] == 3 and arr2.shape[1] == 3:
        z = rgb_z_score(arr1, arr2)
    else:
        raise Exception("Not implemented")

    return 2 - 2 * norm.cdf(np.abs(z))
