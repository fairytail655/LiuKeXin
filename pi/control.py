import time
import serial

ser_app = serial.Serial("/dev/ttyUSB0", 9600)
ser_car = serial.Serial("/dev/ttyAMA0", 9600)

while True:
#    num = ser_app.readline()
    num = ser_app.read(1)
    try:
        if num == b'w':
            ser_car.write(b"3")
            print(3)
        elif num == b'l':
            ser_car.write(b"1")
            print(1)
        elif num == b'r':
            ser_car.write(b"2")
            print(2)
        else:
            ser_car.write(b"0")
            print(0)
        time.sleep(0.1);
    except:
        print("error")

