#!/bin/bash

sudo GBOT_ROOT_DIR=$GBOT_ROOT_DIR venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:9090 --error-logfile - --access-logfile - feed:app
