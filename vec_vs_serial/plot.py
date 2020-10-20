import matplotlib.pyplot as plt
import numpy as np
title = 'Vector fused multiply add benchmark it = 10M'
ser = np.genfromtxt('ser-benchmark.data', delimiter=' ')  
vec = np.genfromtxt('vec-benchmark.data', delimiter=' ')
plt.figure()
plt.title(title)
plt.plot(ser[:, 0], ser[:, 3], marker='^', label='serial')
plt.plot(vec[:, 0], vec[:, 3], marker='o', label='AVG vectorized')
plt.xlabel('FLOP per loop iteration')
plt.ylabel('Time [s]')
plt.legend()
#plt.show()
plt.savefig('time_vec_vs_ser_vector_op.pdf')

plt.figure()
plt.title(title)
plt.plot(ser[:, 0], vec[:, 3] / vec[:, 3], marker='^', label='serial')

plt.plot(vec[:, 0], ser[:, 3] / vec[:, 1], marker='o', label='BEST    vectorized')
plt.plot(vec[:, 0], ser[:, 3] / vec[:, 2], marker='o', label='WORST   vectorized')
plt.plot(vec[:, 0], ser[:, 3] / vec[:, 3], marker='o', label='AVERAGE vectorized')

plt.xlabel('FLOP per loop iteration')
plt.ylabel('Speedup')
plt.legend()
#plt.show()
plt.savefig('speedup_vec_vs_ser_vector_op.pdf')
