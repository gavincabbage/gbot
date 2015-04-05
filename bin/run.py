import sys
import os
sys.path.append(os.getenv('GBOT_ROOT_DIR'))

from web import app

if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8080)
