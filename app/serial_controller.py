import serial


class SerialController(object):

    FORWARD = 10
    BACK = 11
    LEFT = 12
    RIGHT = 13
    STOP = 14
    PAN_CENTER = 20
    PAN_LEFT = 21
    PAN_RIGHT = 22

    def __init__(self, device=str(), rate=9600, timeout=1):
        self.device = device
        self.rate = rate
        self.timeout = timeout
        self.connection = serial.Serial(self.device, self.rate, timeout=self.timeout)

    def move(self, direction):
        if direction == "forward":
            self._write(self.FORWARD)
        elif direction == "back":
            self._write(self.BACK)
        elif direction == "left":
            self._write(self.LEFT)
        elif direction == "right":
            self._write(self.RIGHT)
        elif direction == "stop":
            self._write(self.STOP)

    def look(self, direction):
        if direction == "center":
            self._write(self.PAN_CENTER)
        elif direction == "left":
            self._write(self.PAN_LEFT)
        elif direction == "right":
            self._write(self.PAN_RIGHT)

    def readline(self):
        return self.connection.readline()

    def _write(self, code):
        self.connection.write(str(code))
