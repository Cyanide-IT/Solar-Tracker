import serial
import time

USB_serial_port = '/dev/ttyACM0'

START_CODE = b's'       #Start Arduino
FOUND_CODE = 'f'        #Arduino found the sun
TERMINATE_CODE = b't'   #Kill the Arduino process

ser = serial.Serial(USB_serial_port, 9600)
ser.flushInput()

ser.write(START_CODE)

out_message = "-----\nFound sun\n"
in_message = 0
found = False
terminate_time = 0

while True:
    if ser.in_waiting > 0:
        print("got something")
        in_message = ser.readline().decode("utf-8")
        #if in_message == FOUND_CODE:
        i = int(0)
        while i < 2:
            if ser.in_waiting > 0:
                out_message += ("\t" + ser.readline().decode("utf-8"))
                i += 1
                #time.sleep(.100)

        print(out_message)
        print("----------")
        found = True
        terminate_time = time.time() + 3
        break
    #time.sleep(.300)
if found:
    while True:
        if time.time() < terminate_time:
            time.sleep(1)
        else:
            break
    ser.write(TERMINATE_CODE)
    print("\n---------\nTerminated Arduino, exiting program...\n")

#mark 4
