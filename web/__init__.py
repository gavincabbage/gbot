__all__ = ['app', 'serial_controller', 'distance_sensor']


from os import getenv
from flask import Flask


app = Flask(__name__)


config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)


i2c_controller = None
if app.config['I2C_ENABLED']:

    from externals.i2c_controller import I2CController
    i2c_controller = I2CController()


distance_sensor = None
if app.config['DISTANCE_SENSOR_ENABLED']:

    from externals.distance_sensor import DistanceSensor
    distance_sensor = DistanceSensor(app.config['DISTANCE_TRIG_PIN'],
                                     app.config['DISTANCE_ECHO_PIN'])


from web.routes import *
