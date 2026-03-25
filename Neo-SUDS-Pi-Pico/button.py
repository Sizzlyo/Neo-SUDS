from machine import Timer, Pin
import time
import asyncio

class Button:
    def __init__(self, pin, debounce = 0.01):
        self.toggle = False
        self.state = 0
        self.button = Pin(pin, mode=Pin.IN, pull=Pin.PULL_UP)
        self.debounce = debounce
        
        
    def value(self):
        return button.value()
    
    def monitor(self):
        #print("lol")
        new_button_state = self.button.value()
        if new_button_state is not self.state:
            if self.state == 0:
                self.state = 1
            elif self.state == 1:
                self.state = 0
            if new_button_state is 0:
                self.toggle = not self.toggle
                time.sleep(self.debounce)
        #await asyncio.sleep(1)