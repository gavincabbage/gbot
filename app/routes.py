from flask import render_template

from app import app


@app.route('/', methods=['GET'])
def index():

    return render_template('index.html', feed_url=app.config['FEED_URL'])


@app.route('/look/<string:direction>')
def look(direction):

    if app.config['EXTERNALS_ENABLED']:
        from app import serial
        serial.look(direction)
    else:
        print "PRETEND_TO_LOOK"

    return str(), 200


@app.route('/move/<string:direction>')
def move(direction):

    if app.config['EXTERNALS_ENABLED']:
        from app import serial
        serial.move(direction)
    else:
        print "PRETEND_TO_MOVE"

    return str(), 200
