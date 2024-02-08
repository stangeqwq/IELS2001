import serial
from time import sleep

# Define the serial port and baud rate
serial_port = "/dev/serial0"  # Adjust this based on your Raspberry Pi's configuration
baud_rate = 115200

# Open the serial port
ser = serial.Serial(serial_port, baud_rate, timeout=1)

try:
    while True:
        # Read data from the serial port
        data = ser.readline().decode('utf-8').strip()

        # Print the received data
        print("Received:", data)
        sleep(0.3)
        input_command = input("Command to execute (On/Off):")
        message = input_command + "\n"
        ser.write(message.encode('utf-8'))
        print("Sending:",message.encode('utf-8'))
        sleep(0.3)

except KeyboardInterrupt:
    # Close the serial port when the script is interrupted (e.g., Ctrl+C)
    ser.close()
    print("Serial port closed.")
