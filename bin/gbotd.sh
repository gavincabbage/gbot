#!/bin/bash

export GBOT_ROOT_DIR=/home/gbot/gbot

gbot_logfile="/tmp/gbot_log.txt"

cd ${GBOT_ROOT_DIR}
venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:8088 --error-logfile - --access-logfile - web:app >> ${gbot_logfile} 2>&1
