import numpy as np
import polyfit_curved_lane
import cv2
import sys
import matplotlib.pyplot as plt
 
# hoge = np.zeros((2, 3))
img = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE)

curve_x_from_y = polyfit_curved_lane.polyfit(img, int(sys.argv[2]))

print(curve_x_from_y)

plt.plot(curve_x_from_y)
plt.xlim(300, 720)
plt.ylim(100, 600)
plt.legend()
plt.show()

