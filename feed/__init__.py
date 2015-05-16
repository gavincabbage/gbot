__all__ = ['app']


from os import getenv
from flask import Flask
from redis import StrictRedis


app = Flask(__name__)

config_file = getenv('GBOT_ROOT_DIR') + '/config/base.py'
app.config.from_pyfile(config_file)

redis = StrictRedis(host='localhost', port=8090, db=0)
redis.set('feed_started', 'true')

import feed.routes
