from sense_hat import SenseHat, ACTION_PRESSED, ACTION_HELD, ACTION_RELEASED
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from signal import pause
import datetime as dt

state = False # False - tekst, True - grafisk
sense = SenseHat()
casevalue = 0 # 0 - temp, 1 - humidity, 2 - pressure
fig = plt.figure()
ax = fig.add_subplot(1, 1, 1)
xs = []
ys = []
def pushed_up(event):
	global casevalue
	if event.action != ACTION_RELEASED:
		casevalue += 1
		casevalue %= 3
		print(casevalue)

def pushed_down(event):
	global casevalue
	if event.action != ACTION_RELEASED:
		casevalue -= 1
		casevalue %= 3
		print(casevalue)
		
def pushed_left(event):
	global casevalue
	if event.action != ACTION_RELEASED:
		casevalue -= 1
		casevalue %= 3
		print(casevalue)

def pushed_right(event):
	global casevalue
	if event.action != ACTION_RELEASED:
		casevalue += 1
		casevalue %= 3
		print(casevalue)
		
def pushed_middle(event):
	global state
	if event.action != ACTION_RELEASED:
		state = not state
		print(state)
def graph(i): # i, frame number, is needed for FuncAnimation (real-time graphing)
	global xs
	global ys
	print("graphing...")
	if casevalue == 0: 
		sensorvalue = sense.get_temperature()
		measurement = "Temperature"
	elif casevalue == 1: 
		sensorvalue = sense.get_humidity()
		measurement = "humidity"
	elif casevalue == 2: 
		sensorvalue = sense.get_pressure()
		measurement = "pressure"
	xs.append(dt.datetime.now().strftime("%H:%M:%S.%f"))
	ys.append(sensorvalue)
	xs = xs[-20:]
	ys = ys[-20:]
	ax.clear()
	ax.plot(xs, ys)
	plt.title(f"{measurement} over Time")
	plt.xticks(rotation=45, ha='right')
	plt.subplots_adjust(bottom=0.30)
	plt.ylabel(f"{measurement}")

def text(casevalue):
	if casevalue == 0: print("Temperature:", temp, "C")
	elif casevalue == 1: print("Humidity:", humidity, "%%rH")
	elif casevalue == 2: print("Pressure:", pressure, "millibar")
	
while True:
	temp = sense.get_temperature()
	humidity = sense.get_humidity()
	pressure = sense.get_pressure()
	sense.stick.direction_up = pushed_up
	sense.stick.direction_down = pushed_down
	sense.stick.direction_left = pushed_left
	sense.stick.direction_right = pushed_right
	sense.stick.direction_middle = pushed_middle
	if state:
		ani = animation.FuncAnimation(fig, graph, interval=100)
		plt.show()
	else: text(casevalue) 
