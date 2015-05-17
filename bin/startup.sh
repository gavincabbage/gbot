#!/bin/bash


export GBOT_ROOT_DIR="/home/gbot/gbot"

name=`basename "$0"`
logfile="/tmp/gbotd_log.txt"


log()
{
    echo ${name}": $1" >> ${logfile} 2>&1
}

load_config_into_redis()
{
    log "loading config into reddis..."
    venv/bin/python bin/load_redis.py config/config.json >> ${logfile} 2>&1
}

start_feed()
{
    log "starting feed..."
    venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:8089 \
            --error-logfile ${logfile} --access-logfile ${logfile} feed:app &
    feed_pid="$!"
    log "feed_pid=${feed_pid}"
    redis-cli -p 8090 -n 0 set feed_pid "${feed_pid}" >> ${logfile} 2>&1
}

start_web()
{
    log "starting web..."
    venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:8088 \
            --error-logfile ${logfile} --access-logfile ${logfile} web:app &
    web_pid="$!"
    log "web_pid=${web_pid}"
    redis-cli -p 8090 -n 0 set web_pid "${web_pid}" >> ${logfile} 2>&1
}

start()
{
    cd ${GBOT_ROOT_DIR}
    load_config_into_redis
    start_feed
    start_web
}


start
exit 0