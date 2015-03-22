import sys
import os
sys.path.append('/home/gbot/gbot')

from app import app

if __name__ == '__main__':
	app.run(host='0.0.0.0', port=8080)
