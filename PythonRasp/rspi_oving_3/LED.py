import RPi.GPIO as GPIO
from time import sleep

led_pin = 12

def setup():
    print("inside setup")
    GPIO.setmode(GPIO.BOARD)

    print(GPIO.getmode())

    GPIO.setup(led_pin, GPIO.OUT)

def loop():
    GPIO.output(led_pin, GPIO.HIGH)
    sleep(1)
    GPIO.output(led_pin, GPIO.LOW)
    sleep(1)
    

def main():
    print("inside main")
    setup()
    while True:
        loop()
if __name__ == "__main__":
    main()