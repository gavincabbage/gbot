import RPi.GPIO as gpio
import time


class CameraServo(object):

    CENTER = 7.5
    LEFT = 5.0
    RIGHT = 10.0

    def __init__(self):
        gpio.setmode(gpio.BOARD)
        gpio.setup(7, gpio.OUT)
        self.pwm = gpio.PWM(7,50)
        self.pwm.start(self.CENTER)

    def test(self):
        time.sleep(1)
        self.pwm.ChangeDutyCycle(self.LEFT)
        time.sleep(1)
        self.pwm.ChangeDutyCycle(self.RIGHT)
        time.sleep(1)
        self.pwm.ChangeDutyCycle(self.CENTER)
        time.sleep(1)

    def look_center(self):
        self.pwm.start(self.CENTER)

    def look_left(self):
        self.pwm.start(self.LEFT)

    def look_right(self):
        self.pwm.start(self.RIGHT)

    def cleanup(self):
        self.pwm.stop()
        gpio.cleanup()
