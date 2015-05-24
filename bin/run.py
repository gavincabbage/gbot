import sys
import os
sys.path.append(os.getenv('GBOT_ROOT_DIR'))

from web import app

if __name__ == '__main__':
    ip = os.environ['IP']
    port = int(os.environ['PORT'])
    print ip
    print port
    app.run(host=ip, port=port)
