import sys
import os
sys.path.append(os.getenv('GBOT_ROOT_DIR'))

from app.serial import SerialController

if __name__ == '__main__':
	serial = SerialController()
