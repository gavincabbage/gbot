__all__ = ['app']


from flask import Flask
from redis import StrictRedis


def get_bool(key, r):
    return r.get(key) == 'true'


app = Flask(__name__)

redis = StrictRedis(host='localhost', port=8090, db=0)
app.config['DEBUG'] = redis.get_bool('feed.debug', redis)
app.config['CAMERA_ENABLED'] = redis.get_bool('feed.camera_enabled', redis)
app.config['FEED_TIMEOUT'] = redis.get_bool('feed.timeout', redis)

import feed.routes

redis.set('feed_started', 'OK')
