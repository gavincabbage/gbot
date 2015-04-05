from flask import render_template

from web import app, serial


@app.route('/', methods=['GET'])
def index():

    return render_template('index.html', feed_url=app.config['FEED_URL'])


@app.route('/look/<string:direction>')
def look(direction):

    if serial:
        serial.look(direction)

    return str(), 200


@app.route('/move/<string:direction>')
def move(direction):

    if serial:
        serial.move(direction)

    return str(), 200
