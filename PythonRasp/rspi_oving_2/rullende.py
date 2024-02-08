from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

x = 3
y = 3

def clamp(value, min_value=0, max_value=7):
    return min(max_value, max(min_value, value))

def pushed_up():
    global y
    y = clamp(y - 1)
    refresh()

def pushed_down():
    global y
    y = clamp(y + 1)
    refresh()
def pushed_left():
    global x
    x = clamp(x - 1)
    refresh()

def pushed_right():
    global x
    x = clamp(x + 1)
    refresh()
def refresh():
    sense.clear()
    sense.set_pixel(x, y, 255, 255, 255)

while True:
    gyro_only = sense.get_gyroscope()
    roll = gyro_only['roll']
    pitch = gyro_only['pitch']
    yaw = gyro_only['yaw']
    #print(gyro_only)
    print(f"p: {pitch}, r: {roll}, y: {yaw}")

    # alternatives
    #print(sense.gyro)
    #print(sense.gyroscope)
    # followed from axis given in https://projects.raspberrypi.org/en/projects/tightrope/4
    if pitch > 30 and pitch < 90: pushed_left()
    if pitch > 90: pushed_right()
    if roll > 30 and roll < 90: pushed_down()
    if roll > 90: pushed_up()
    #sleep(1)
