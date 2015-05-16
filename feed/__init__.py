__all__ = ['app']


from flask import Flask
from externals.redis import RedisClient


app = Flask(__name__)

redis = RedisClient(host='localhost', port=8090, db=0)
app.config['DEBUG'] = redis.get_bool('debug')
app.config['CAMERA_ENABLED'] = redis.get_bool('camera_enabled')
app.config['FEED_TIMEOUT'] = redis.get_bool('feed_timeout')

import feed.routes

redis.set('feed_started', 'OK')
