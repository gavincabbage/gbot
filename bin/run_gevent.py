import sys
import os
sys.path.append(os.getenv('GBOT_ROOT_DIR'))

from gevent.wsgi import WSGIServer
from app import app

if __name__ == '__main__':
	#app.run(host='0.0.0.0', port=8080)
    http_server = WSGIServer(('0.0.0.0', 8080), app)
    http_server.serve_forever()
