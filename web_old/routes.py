from flask import render_template

from web import app, distance_sensor


@app.route('/', methods=['GET'])
def index():

    return render_template('index.html', feed_url=app.config['FEED_URL'])


@app.route('/distance')
def distance():

    if distance_sensor:
        result = distance_sensor.sense()
        return str(result), 200

    return "42.00", 200
