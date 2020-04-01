import numpy as np
import polyfit_curved_lane
 
hoge = np.zeros((2, 3))
hoge[1][1] = 11
hoge[0][1] = 1
hoge[1][0] = 10

polyfit_curved_lane.polyfit(hoge)

