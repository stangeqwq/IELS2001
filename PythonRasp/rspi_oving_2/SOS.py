from sense_hat import SenseHat
from time import sleep
sense = SenseHat()

X = [255, 0 ,255]
O = [0, 0, 0]
S_letter = [
        O, O, O, X, O, O, O, O,
        O, O, X, O, X, O, O, O,
        O, O, X, O, O, O, O, O,
        O, O, O, X, O, O, O, O,
        O, O, O, O, X, O, O, O,
        O, O, X, O, X, O, O, O,
        O, O, O, X, O, O, O, O,
        O, O, O, O, O, O, O, O,
        ]
O_letter = [
        O, O, O, X, X, O, O, O,
        O, O, X, O, O, X, O, O,
        O, O, X, O, O, X, O, O,
        O, O, X, O, O, X, O, O,
        O, O, X, O, O, X, O, O,
        O, O, X, O, O, X, O, O,
        O, O, O, X, X, O, O, O,
        O, O, O, O, O, O, O, O,
        ]
while True:
    sense.set_pixels(S_letter)
    sleep(0.5)
    sense.clear()
    sleep(0.5)
    sense.set_pixels(S_letter)
    sleep(0.5)
    sense.clear()
    sleep(0.5)
    sense.set_pixels(S_letter)
    sleep(0.5)
    sense.clear()
    sleep(0.5)
    sense.set_pixels(O_letter)
    sleep(1.5)
    sense.clear()
    sleep(0.5)
    
