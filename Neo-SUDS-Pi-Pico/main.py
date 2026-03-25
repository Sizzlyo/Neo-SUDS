from machine import Timer, Pin
import time
import asyncio
import network
import socket
import button
          
button_20 = button.Button(20)
button_21 = button.Button(21)

led_19 = Pin(19, mode=Pin.OUT)
led_28 = Pin(28, mode=Pin.OUT)

ssid = "GalaxyS23"
password = "YourMother"


async def connect():
        wlan = network.WLAN(network.STA_IF)
        wlan.active(True)
        wlan.connect(ssid, password)
        while wlan.isconnected() == False:
            print('Waiting for connection...')
            await asyncio.sleep(1)
        ip = wlan.ifconfig()[0]
        print(ip)
        connection = open_socket(ip)
        print(connection)
        # while True:
        #     client = connection.accept()[0]
        #     request = client.recv(1024)
        #     request = str(request)
        #     try:
        #         request = request.split()[1]
        #     except IndexError:
        #         pass
        #     if request =='/lol?':
        #        client.send("lol")
        #     elif request == '/close?':
        #        sys.exit()
        #     html = webpage(temperature, state)
        #     client.close()
        #     print("lol")
        #     await asyncio.sleep(1)
                
def open_socket(ip):
    address = (ip, 33199)
    connection = socket.socket()
    connection.bind(address)
    connection.listen(1)
    return connection
    

def led_toggle(led, button):
        if button.toggle:
            led.on()
        if not button.toggle:
            led.off()

async def buttons():
    while True:
        button_20.monitor()
        button_21.monitor()
        led_toggle(led_19, button_20)
        led_toggle(led_28, button_21)
        await asyncio.sleep(0.1)
        
async def main():
    await asyncio.gather(asyncio.create_task(connect()), asyncio.create_task(buttons()))
    
if __name__ == "__main__":
    asyncio.run(main())