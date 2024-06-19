import serial
import serial.tools.list_ports

import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation



def selectPorts():
    commports = serial.tools.list_ports.comports()
    numPorts = len(commports)
    if (numPorts == 0):
        print("No serial ports available¥n¥n")
        exit()
    if (numPorts > 1):
        # Have usr pick one
        portNum = 0
        for port in commports:
            print("port number ", portNum)
            print(port)
            portNum += 1
        usePort = int(input('enter port number to use 0-'+str(numPorts-1)+' -> '))
    else:
        usePort = 0
    
    comport = commports[usePort][0]
    print('using ',comport,'¥n')
    return(comport)

def readserial(comport, baudrate):
    ser = serial.Serial(comport, baudrate, timeout=0.1)

    while True:
        data = ser.readline().decode().strip()
        timestamp = time.strftime('%m/%d %H:%M:%S')
        if data:
            print(data, timestamp)

def plot(data):
    plt.cla()
    addValue = int(ser.readline().decode().strip())
    x_array[:-1] = x_array[1:]
    x_array[-1] = addValue
    print(addValue)
    rand = x_array
    plt.plot(rand)

if __name__ == '__main__':
    comport = selectPorts()
    #readserial(comport, 9600)
    ser = serial.Serial(comport, 9600)
    fig = plt.figure()
    x_max = 86400
    x_array = [0] * x_max

    #while len(x_array) != x_max:
    #    x_array.append(int(ser.readline().decode().strip()))

    ani = animation.FuncAnimation(fig, plot, interval=1)
    plt.show()
    ser.close()