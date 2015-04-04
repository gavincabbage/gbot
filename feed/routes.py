from flask import render_template, Response

from feed import app


@app.route('/feed')
def feed():

    if app.config['CAMERA_ENABLED']:
        from feed.camera import generate_feed, Camera
        return Response(generate_feed(Camera()),
                        mimetype='multipart/x-mixed-replace; boundary=frame')
    else:
        return str(), 200
