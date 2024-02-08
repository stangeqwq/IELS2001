from sense_hat import SenseHat
from time import sleep
import numpy as np
sense = SenseHat()
R = [255, 0 ,0]
Y = [255, 255, 0]
G = [0, 255 ,0]
P = [255, 0, 255]
W = [255, 255 ,255]
B = [0, 0, 0]



kompass = [
        B, B, P, R, P, B, B, B,
        B, P, B, B, B, P, B, B,
        P, B, B, B, B, B, P, B,
        G, B, B, B, B, B, Y, B,
        P, B, B, B, B, B, P, B,
        B, P, B, B, B, P, B, B,
        B, B, P, W, P, B, B, B,
        B, B, B, B, B, B, B, B,
        ]

while True:
	north = sense.get_compass()
	print("North: %s"%north)
	sense.set_pixels(kompass)
	# centered at pixel [3, 3]
	sense.set_pixel(int(np.sqrt(3)*np.cos(north) + 3), int(-np.sqrt(3)*np.sin(north) + 3), 255, 0, 0)
	print("Coordinate point:", int(3 + np.sqrt(3)*np.cos(north)), int(3 + -np.sqrt(3)*np.sin(north))) # - sin since downwards is minus
