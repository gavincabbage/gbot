from flask import render_template

from web import app, i2c_controller, distance_sensor


@app.route('/', methods=['GET'])
def index():

    return render_template('index.html', feed_url=app.config['FEED_URL'])


@app.route('/look/<string:direction>')
def look(direction):

    if i2c_controller:
        i2c_controller.look(direction)

    return str(), 200


@app.route('/move/<string:direction>')
def move(direction):

    if i2c_controller:
        i2c_controller.move(direction)

    return str(), 200


@app.route('/distance')
def distance():

    if distance_sensor:
        result = distance_sensor.sense()
        return str(result), 200

    return "42.00", 200
