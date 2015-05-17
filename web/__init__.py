__all__ = ['app', 'serial_controller', 'distance_sensor']


from flask import Flask
from redis import StrictRedis


def get_bool(key, r):
    return r.get(key) == 'True'


app = Flask(__name__)

redis = StrictRedis(host='localhost', port=8090, db=0)
app.config['DEBUG'] = get_bool('web.debug', redis)
app.config['I2C_ENABLED'] = get_bool('core.i2c_enabled', redis)
app.config['I2C_ENABLED'] = get_bool('core.distance_sensor_enabled', redis)
app.config['FEED_URL'] = redis.get('feed.paths.root')
trig_pin = int(redis.get('core.trig_pin'))
echo_pin = int(redis.get('core.echo_pin'))


i2c_controller = None
if app.config['I2C_ENABLED']:
    from externals.i2c_controller import I2CController
    i2c_controller = I2CController()


distance_sensor = None
if app.config['DISTANCE_SENSOR_ENABLED']:
    from externals.distance_sensor import DistanceSensor
    distance_sensor = DistanceSensor(trig_pin, echo_pin)


from web.routes import *

redis.set('web_started', 'OK')
