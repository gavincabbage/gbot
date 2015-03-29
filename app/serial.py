from serial import Serial

class SerialController(object):

	FORWARD = 10
	BACK = 11
	LEFT = 12
	RIGHT = 13
	PAN_CENTER = 20
	PAN_LEFT = 21
	PAN_RIGHT = 22

	def __init__(self, device=str(), rate=9600, timeout=1):
		self.connection = Serial(device, rate, timeout)

	def move(self, direction):
		if direction == "forward":
			self._write(self.FORWARD)
		elif direction == "back":
			self._write(self.BACK)
		elif direction == "left":
			self._write(self.LEFT)
		elif direction == "right":
			self._write(self.RIGHT)

	def look(self, direction):
		if direction == "center":
			self._Write(self.PAN_FORWARD)
		elif direction == "left":
			self._write(self.PAN_LEFT)
		elif direction == "right":
			self._write(self.PAN_RIGHT)

	def readline(self):
		return self.connection.readlin()

	def _write(self, code):
		self.connection.write(str(chr(code))