import matplotlib.pyplot as plt
import numpy as np
from matplotlib.ticker import EngFormatter

fig, ax = plt.subplots()
ax.set_xscale('log')
formatter = EngFormatter()
ax.xaxis.set_major_formatter(formatter)

xs = np.logspace(1, 9, 100)
ys = xs * np.log10(xs)
ax.plot(xs, ys)

xs = np.logspace(1, 9, 100)
ys = 2 * xs
ax.plot(xs, ys)

plt.show()
