import RPi.GPIO as GPIO
import time 

led1_pin = 12
led2_pin = 10
led1_millis = 0
led2_millis = 0
led1_out = False
led2_out = False

def millis():
    return round(time.time() * 1000)

def setup():
    GPIO.cleanup()
    print("inside setup")
    GPIO.setmode(GPIO.BOARD)

    print(GPIO.getmode())

    GPIO.setup(led1_pin, GPIO.OUT)
    GPIO.setup(led2_pin, GPIO.OUT)

def loop():
    global led1_out
    global led2_out
    global led1_millis
    global led2_millis
    if millis() - led1_millis > 1000: #lets led1 blink every 1 sec while stopping every time 1 sec
        led1_out = not led1_out
        GPIO.output(led1_pin, led1_out)
        led1_millis = millis()
    if millis() - led2_millis > 1500: #blinks led2 every 1.5 sec (emphasize capabiility of non-blocking code)
        led2_out = not led2_out
        GPIO.output(led2_pin, led2_out)
        led2_millis = millis()

def main():
    print("inside main")
    setup()
    while True:
        loop()
if __name__ == "__main__":
    main()