__all__ = ['app']


from os import getenv
from flask import Flask


app = Flask(__name__)


config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)


serial_controller, distance_sensor = None
if app.config['EXTERNALS_ENABLED']:

    from externals.serial_controller import SerialController
    serial_controller = SerialController(app.config['SERIAL_DEVICE'])

    from externals.distance_sensor import DistanceSensor
    distance_sensor = DistanceSensor(app.config['DISTANCE_TRIG_PIN'],
                                     app.config['DISTANCE_ECHO_PIN'])


from web.routes import *
