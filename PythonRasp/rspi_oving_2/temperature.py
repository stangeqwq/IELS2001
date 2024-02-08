from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

R = [255, 0 ,0]
B = [0, 0 ,255]
G = [0, 255 ,0]
O = [255, 165 ,0]
W = [255, 255 ,255]
red = [R for _ in range(64)]
blue = [B for _ in range(64)]
green = [G for _ in range(64)]
orange = [O for _ in range(64)]
white = [W for _ in range(64)]
alert = False
while True:
	humidity = sense.get_humidity()
	temp = sense.get_temperature()
	print("Temperature: %s C" %temp)
	print("Humidity: %s %%rH" %humidity)
	if temp > 25:
		sense.set_pixels(red)
		sleep(0.5)
		alert = True
	if temp < 20:
		sense.set_pixels(blue)
		sleep(0.5)
		alert = True
	if humidity > 50:
		sense.set_pixels(orange)
		sleep(0.5)
		alert = True
	if humidity < 40:
		sense.set_pixels(white)
		sleep(0.5)
		alert = True
	if not alert: 
		sense.set_pixels(green)
		
		
