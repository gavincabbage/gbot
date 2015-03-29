#!/bin/bash

sudo GBOT_ROOT_DIR=$GBOT_ROOT_DIR venv/bin/gunicorn --timeout 3600 -w 4 -b 0.0.0.0:8080 --error-logfile - --access-logfile - app:app
