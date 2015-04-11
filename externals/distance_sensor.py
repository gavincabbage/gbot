import RPi.GPIO as GPIO
import time


class DistanceSensor(object):

    CENTIMETER_COEFF = 17150

    def __init__(self, trig_pin, echo_pin):

        self.trig_pin = trig_pin
        self.echo_pin = echo_pin

        GPIO.setmode(GPIO.BCM)
        GPIO.setup(self.trig_pin, GPIO.OUT)
        GPIO.setup(self.echo_pin, GPIO.IN)
        GPIO.output(self.trig_pin, False)

    def sense(self):

        self._trigger_sensor()
        pulse_duration = self._measure_pulse_duration()
        distance = round(pulse_duration * self.CENTIMETER_COEFF, 2)
        GPIO.cleanup()

        return distance

    def _measure_pulse_duration(self):

        pulse_start = time.time()
        while GPIO.input(self.echo_pin) == 0:
            pulse_start = time.time()

        pulse_end = time.time()
        while GPIO.input(self.echo_pin) == 1:
            pulse_end = time.time()

        return pulse_end - pulse_start

    def _trigger_sensor(self):

        time.sleep(0.1)
        GPIO.output(self.trig_pin, True)
        time.sleep(0.00001)
        GPIO.output(self.trig_pin, False)