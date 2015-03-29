__all__ = ['app', 'camera']


from os import getenv
from flask import Flask


app = Flask(__name__)


config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)

camera_servo, serial = None, None
if app.config['EXTERNALS_ENABLED']:
    from app.serial import SerialControler
    serial = SerialController('/dev/ACM0')


from app.routes import *
