import sys
import os
sys.path.append(os.environ['GBOT_ROOT_DIR'])

from app import app

if __name__ == '__main__':
    app.run(host='0.0.0.0')
