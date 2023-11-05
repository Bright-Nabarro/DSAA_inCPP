#! /usr/bin/env python3
import numpy as np
import matplotlib.pyplot as plt


# Define the data
sizes_1 = [250, 500, 1000, 2000]
times_1 = [0.376, 1.215, 5.872, 54.988]

sizes_2 = [25000, 50000, 100000, 200000, 400000, 800000]
times_2 = [3.669, 8.619, 16.628, 32.212, 79.680, 140.266]

sizes_3 = [100000, 200000, 400000, 800000, 1600000, 3200000, 6400000]
times_3 = [2.442, 5.259, 10.685, 22.484, 48.896, 120.941, 266.705]

# Combine all data
sizes = sizes_1 + sizes_2 + sizes_3
times = times_1 + times_2 + times_3

# Plot the raw data
plt.figure(figsize=(10, 6))
plt.scatter(sizes, times, color='blue', label='Data')

# Try to fit with common time complexity functions
# Linear fit
coeff_linear = np.polyfit(sizes, times, 1)
linear_fit = np.poly1d(coeff_linear)
plt.plot(sizes, linear_fit(sizes), label='Linear fit', linestyle='--')

# Quadratic fit
coeff_quad = np.polyfit(sizes, times, 2)
quad_fit = np.poly1d(coeff_quad)
plt.plot(sizes, quad_fit(sizes), label='Quadratic fit', linestyle='--')

# Logarithmic fit
coeff_log = np.polyfit(np.log(sizes), times, 1)
log_fit = lambda x: coeff_log[0] * np.log(x) + coeff_log[1]
plt.plot(sizes, log_fit(np.array(sizes)), label='Logarithmic fit', linestyle='--')

# Set plot properties
plt.xscale('log')
plt.xlabel('Input Size')
plt.ylabel('Time')
plt.title('Time Complexity Analysis')
plt.legend()
plt.grid(True, which="both", ls="--", c='0.65')

# save the plot as a PNG file
plt.savefig('plot.png')