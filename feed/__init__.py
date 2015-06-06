__all__ = ['app']


from flask import Flask
from redis import StrictRedis


def get_bool(key, r):
    return r.get(key) == 'True'


app = Flask(__name__)

redis = StrictRedis(host='127.0.0.1', port=4290, db=0)
app.config['DEBUG'] = get_bool('feed.debug', redis)
app.config['CAMERA_ENABLED'] = get_bool('feed.camera.enabled', redis)
app.config['TIMEOUT'] = int(redis.get('feed.camera.timeout'))

import feed.routes

redis.set('feed.started', 'OK')
