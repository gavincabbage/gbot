from flask import render_template, Response

from app import app


@app.route('/', methods=['GET'])
def index():
    return render_template('index.html')


@app.route('/feed')
def feed():
    if app.config['CAMERA_ENABLED']:
        return Response(app.camera.generate_feed(app.camera.Camera()),
                        mimetype='multipart/x-mixed-replace; boundary=frame')
    else:
        return str()