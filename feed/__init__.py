__all__ = ['camera']


from os import getenv
from flask import Flask, render_template, Response


app = Flask(__name__)

config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)


@app.route('/feed')
def feed():

    if app.config['CAMERA_ENABLED']:
        from feed.camera import generate_feed, Camera
        return Response(generate_feed(Camera()),
                        mimetype='multipart/x-mixed-replace; boundary=frame')
    else:
        return str(), 200
