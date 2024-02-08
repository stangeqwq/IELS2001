from sense_hat import SenseHat
from time import sleep

sense = SenseHat()

def height(pressure):
	# assumed std pressure and temp
	p1 = 101325 # 1 atm -> Pa
	h1 = 0 # assume ground/sea level
	T1 = 273.15 # 0C -> K 
	p = pressure * (100) # mBar to Pa
	a = -0.0065
	g0 = 9.81
	R = 287.06
	h = (T1/a)*(pow(p/p1, -a*R/g0)-1)+h1
	return h
while True:
	temp = sense.get_temperature()
	humidity = sense.get_humidity()
	pressure = sense.get_pressure()
	print(height(pressure))
	print(pressure)
	sense.show_message("Height:", text_colour=[255,0,255])
	sense.show_message(str(height(pressure)), text_colour=[0,255,0])
