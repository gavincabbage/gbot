from sys import argv, path
from os import getenv
path.append(getenv('GBOT_ROOT_DIR'))

from json import loads
from collections import MutableMapping
from redis import StrictRedis


usage = 'usage: venv/bin/python load_redis.py <config.json>'


def flatten(d, parent_key='', sep='.'):
    # this function taken from here
    # http://stackoverflow.com/questions/6027558/flatten-nested-python-dictionaries-compressing-keys

    items = []
    for k, v in d.items():
        new_key = parent_key + sep + k if parent_key else k
        if isinstance(v, MutableMapping):
            items.extend(flatten(v, new_key, sep=sep).items())
        else:
            items.append((new_key, v))

    return dict(items)


def main():

    if len(argv) != 2:
        print usage
        return 1
    else:
        config_file = argv[1]
        print 'config file: ' + config_file

    with open(config_file, 'r') as f:
        data = loads(f.read())

    flat = flatten(data)

    try:
        redis_host = flat['redis.host']
        redis_port = flat['redis.port']
        redis_db = flat['redis.db']
    except KeyError:
        print 'error: invalid redis config'
        return 2
    else:
        print 'redis config: host=' + redis_host + ', port=' + str(redis_port) + ', db=' + str(redis_db)
        redis = StrictRedis(host=redis_host, port=redis_port, db=redis_db)

    for key in flat:
        redis.set(key, flat[key])


if __name__ == '__main__':
    exit(main())