import socket

import time
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation

server_ip = "0.0.0.0"
server_port = 6342
listen_num = 5
buffer_size = 1024

# split byte from ESP32
def split_bytes(data):
    if len(data) != 6:
        raise ValueError("Input data must be exactly 6 bytes long")
    
    moisture = data[:2]
    humidity = data[2:4]
    temperature = data[4:6]

    return moisture, humidity, temperature

if __name__ == '__main__':
    try:
        # 1. create socket object
        print("Trying to create Socket...")
        tcp_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    except socket.error:
        print("Failed to create Socket")

    # 2. associate socket object and IP address/port
    try:
        print("Tryint to bind socket and IP address...")
        tcp_server.bind((server_ip, server_port))
    except:
        print("Failed to bind")
    print("socket IP bind completed")

    # 3. enable socket object
    tcp_server.listen(listen_num)
    print("socket object enabled")

    # 4. loop and wait
    while True:
        print("Start connecting to the client")
        # 5. Connect to the client
        try:
            client, address = tcp_server.accept()
            print(address)
            print("[*] Connected!! [ Source : {}]".format(address))
        except:
            print("Connection failed...")

        
        data = client.recv(buffer_size)
        print("[*] Received Data : {}".format(data))

        moisture, humidity, temperature = split_bytes(data)

        imoisture = int.from_bytes(moisture, byteorder="little")
        ihumidity = int.from_bytes(humidity, byteorder="little")
        itemperature = int.from_bytes(temperature, byteorder="little")

        print(f"Moisture Level: {imoisture}")
        print(f"Humidity: {ihumidity} %")
        print(f"Temperature: {itemperature} C")

        client.send(b"ACK!!")

        client.close()




