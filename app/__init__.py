__all__ = ['app', 'camera', 'servo']


from os import getenv
from flask import Flask


app = Flask(__name__)


config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)

camera_servo = None
if app.config['EXTERNALS_ENABLED']:
    from app.servo import CameraServo
    camera_servo = CameraServo()


from app.routes import *