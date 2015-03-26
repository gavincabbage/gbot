from flask import render_template, Response

from app import app


@app.route('/', methods=['GET'])
def index():

    return render_template('index.html')


@app.route('/feed')
def feed():

    if app.config['EXTERNALS_ENABLED']:
        from app.camera import generate_feed, Camera
        return Response(generate_feed(Camera()),
                        mimetype='multipart/x-mixed-replace; boundary=frame')
    else:
        return str()


@app.route('/look/<string:direction>')
def look(direction):

    if app.config['EXTERNALS_ENABLED']:
        from app import camera_servo
        try:
            camera_servo.__dict__['look_'+direction]
        except KeyError:
            pass
        # if direction == "center":
        #     camera_servo.look_center()
        # elif direction == "left":
        #     camera_servo.look_left()
        # elif direction == "right":
        #     camera_servo.look_right()

    return str(), 200


@app.route('/move/<string:direction>')
def move(direction):

    return str(), 200