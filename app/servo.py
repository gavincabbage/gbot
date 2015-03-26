import RPi.GPIO as gpio
import time

gpio.setmode(gpio.BOARD)
gpio.setup(7, gpio.OUT)

p = gpio.PWM(7,50)

p.start(7.5)
time.sleep(1)
p.ChangeDutyCycle(12.5)
time.sleep(1)
p.ChangeDutyCycle(2.5)
time.sleep(1)
p.ChangeDutyCycle(7.5)
time.sleep(1)
	
p.stop()
gpio.cleanup()
exit(0)


