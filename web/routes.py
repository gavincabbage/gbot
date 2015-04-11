from flask import render_template

from web import app, serial_controller


@app.route('/', methods=['GET'])
def index():

    return render_template('index.html', feed_url=app.config['FEED_URL'])


@app.route('/look/<string:direction>')
def look(direction):

    if serial_controller:
        serial_controller.look(direction)

    return str(), 200


@app.route('/move/<string:direction>')
def move(direction):

    if serial_controller:
        serial_controller.move(direction)

    return str(), 200


@app.route('/distance')
def distance():

    pass
