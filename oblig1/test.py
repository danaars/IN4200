import numpy as np

"""
Double checking that the CRS matrix-vector multiplication
works as intended.
"""

M = np.array([[0, 0, 0, 0, 0, 0, 1/3, 0],
            [1/2, 0, 1/2, 1/3, 0, 0, 0, 0],
            [1/2, 0, 0, 0, 0, 0, 0, 0],
            [0, 1, 0, 0, 0, 0, 0, 0],
            [0, 0, 1/2, 1/3, 0, 0, 1/3, 0],
            [0, 0, 0, 1/3, 1/3, 0, 0, 1/2],
            [0, 0, 0, 0, 1/3, 0, 0, 1/2],
            [0, 0, 0, 0, 1/3, 1, 1/3, 0]])

x = np.array([1, 2, 3, 4, 1, 2, 3, 4])

print(np.matmul(M, x))
