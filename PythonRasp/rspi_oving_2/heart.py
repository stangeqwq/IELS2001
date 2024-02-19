from sense_hat import SenseHat
from time import sleep
sense = SenseHat()

X = [255, 0 ,0]
O = [0, 0, 0]
big_heart = [
        O, O, O, O, X, X, X, O,
        O, O, X, X, X, X, X, X,
        O, X, X, X, X, X, X, X,
        X, X, X, X, X, X, X, O,
        X, X, X, X, X, X, X, O,
        O, X, X, X, X, X, X, X,
        O, O, X, X, X, X, X, X,
        O, O, O, O, X, X, X, O,
        ]
small_heart = [
        O, O, O, O, O, O, O, O,
        O, O, O, O, X, X, X, O,
        O, O, X, X, X, X, X, O,
        O, X, X, X, X, X, O, O,
        O, X, X, X, X, X, O, O,
        O, O, X, X, X, X, X, O,
        O, O, O, O, X, X, X, O,
        O, O, O, O, O, O, O, O,
        ]
while True:
    sense.set_pixels(big_heart)
    sleep(0.2)
    sense.set_pixels(small_heart)
    sleep(0.2)
    sense.set_pixels(big_heart)
    sleep(0.6)
 
