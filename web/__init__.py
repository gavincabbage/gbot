__all__ = ['app']


from os import getenv
from flask import Flask


app = Flask(__name__)


config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)

serial = None
if app.config['EXTERNALS_ENABLED']:
    from externals.serial_controller import SerialController
    serial = SerialController(app.config['SERIAL_DEVICE'])


from web.routes import *
