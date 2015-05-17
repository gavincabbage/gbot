__all__ = ['app', 'serial_controller', 'distance_sensor']


from os import getenv
from flask import Flask
from redis import StrictRedis


def get_bool(key, r):
    return r.get(key) == 'true'


app = Flask(__name__)


config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)

redis = StrictRedis(host='localhost', port=8090, db=0)
app.config['DEBUG'] = redis.get_bool('web.debug', redis)
app.config['I2C_ENABLED'] = redis.get_bool('core.i2c_enabled', redis)
app.config['DISTANCE_SENSOR_ENABLED'] = redis.get_bool('core.distance_sensor_enabled', redis)


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
