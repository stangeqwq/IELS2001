# Set up libraries and overall settings
import RPi.GPIO as GPIO  # Imports the standard Raspberry Pi GPIO library
import time 
from rpi_hardware_pwm import HardwarePWM

pwm = HardwarePWM(pwm_channel=0, hz=50, chip=0) #GPIO 18 - PWM-CHANNEL 0, 19 - CHANNEL 1
pwm.start(7.5) # full duty cycle 90 degrees hardware

try:
    while True:
        # Sweep from 0 to 180 degrees
        for angle in range(0, 181, 10):
            # Convert angle to duty cycle (2.5% to 12.5%)
            duty_cycle = 2.5 + (angle / 18.0)
            print(duty_cycle)
            # Change duty cycle
            pwm.change_duty_cycle(duty_cycle)
            
            # Wait for the servo to reach the position
            time.sleep(0.3)
            
        # Sweep back from 180 to 0 degrees
        for angle in range(180, -1, -10):
            duty_cycle = 2.5 + (angle / 18.0)
            pwm.change_duty_cycle(duty_cycle)
            time.sleep(0.3)

except KeyboardInterrupt:
    # Stop PWM and cleanup GPIO on Ctrl+C
    pwm.stop()
    GPIO.cleanup()

pwm.stop()

# Define GPIO pin for PWM
servo_pin = 18

# Set the GPIO mode and setup the pin
GPIO.setmode(GPIO.BCM)
GPIO.setup(servo_pin, GPIO.OUT)

# Create a PWM instance with a frequency of 50 Hz
pwm = GPIO.PWM(servo_pin, 50)

# Start PWM with a duty cycle of 7.5% (90 degrees)
pwm.start(7.5)
try:
    while True:
        # Sweep from 0 to 180 degrees
        for angle in range(0, 181, 10):
            # Convert angle to duty cycle (2.5% to 12.5%)
            duty_cycle = 2.5 + (angle / 18.0)
            print(duty_cycle)
            # Change duty cycle
            pwm.ChangeDutyCycle(duty_cycle)
            
            # Wait for the servo to reach the position
            time.sleep(0.3)
            
        # Sweep back from 180 to 0 degrees
        for angle in range(180, -1, -10):
            duty_cycle = 2.5 + (angle / 18.0)
            print(duty_cycle)
            pwm.ChangeDutyCycle(duty_cycle)
            time.sleep(0.3)

except KeyboardInterrupt:
    # Stop PWM and cleanup GPIO on Ctrl+C
    pwm.stop()
    GPIO.cleanup()