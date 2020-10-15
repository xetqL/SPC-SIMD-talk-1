import matplotlib.pyplot as plt
import numpy as np

ser = np.genfromtxt('ser-benchmark.data', delimiter=' ')  
vec = np.genfromtxt('vec-benchmark.data', delimiter=' ')
plt.title('Vector multiplication benchmark loop = (1M * X FLOP)')
plt.plot(ser[:, 0], ser[:, 1], marker='^', label='serial')
plt.plot(vec[:, 0], vec[:, 1], marker='o', label='vectorized')
plt.xlabel('MFLOP')
plt.ylabel('Time [s]')
plt.legend()
plt.show()

plt.title('Vector multiplication benchmark loop = (1M * X FLOP)')
plt.plot(ser[:, 0], vec[:, 1] / vec[:, 1], marker='^', label='serial')
plt.plot(vec[:, 0], ser[:, 1] / vec[:, 1], marker='o', label='vectorized')
plt.xlabel('MFLOP')
plt.ylabel('Speedup')
plt.legend()
plt.show()
