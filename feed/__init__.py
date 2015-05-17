__all__ = ['app']


from flask import Flask
from redis import StrictRedis


def get_bool(key, r):
    return r.get(key) == 'True'


app = Flask(__name__)

redis = StrictRedis(host='localhost', port=8090, db=0)
app.config['DEBUG'] = get_bool('feed.debug', redis)
app.config['CAMERA_ENABLED'] = get_bool('feed.camera_enabled', redis)
app.config['FEED_TIMEOUT'] = int(redis.get('feed.timeout'))

import feed.routes

redis.set('feed_started', 'OK')
