import smbus


class I2CController(object):

    arduino1 = 0x04
    arduino2 = 0x05

    moves = {
        "forward": 10,
        "back": 11,
        "left": 12,
        "right": 13,
        "stop": 14
    }

    looks = {
        "center": 20,
        "left": 21,
        "right": 22,
        "up": 23,
        "down": 24
    }

    def __init__(self):
        self.bus = smbus.SMBus(1)
        
    def move(self, direction):
        self.bus.write_byte(self.arduino1, self.moves[direction])

    def look(self, direction):
        self.bus.write_byte(self.arduino2, self.looks[direction])

    def status(self, arduino_number):
        return self.bus.read_byte(self.arduino1) \
            if arduino_number == 1 else self.bus.read_byte(self.arduino2)
