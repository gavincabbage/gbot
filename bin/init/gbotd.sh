#! /bin/sh

### BEGIN INIT INFO
# Provides:          gbotd
# Required-Start:    $local_fs $remote_fs $syslog $network $time $redis-server
# Required-Stop:     $local_fs $remote_fs $syslog $network $time $redis-server
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: gbotd initscript
# Description:       This file should be named to 'gbotd' placed in /etc/init.d.
### END INIT INFO

export GBOT_ROOT_DIR="/home/gbot/gbot"

usage="Usage: /etc/init.d/servod start|stop|restart"
initfile=`basename "$0"`
logfile="/tmp/gbotd_log.txt"
web_pid=""
feed_pid=""

exit_success=0
exit_usage=1

log()
{
    echo ${initfile}": $1" >> ${logfile} 2>&1
}

start()
{
    cd ${GBOT_ROOT_DIR}
    
    log "starting feed..."
    venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:8089 \
            --error-logfile ${logfile} --access-logfile ${logfile} feed:app &
    feed_pid="$!"
    log "feed_pid=${feed_pid}"
    
    log "starting web..."
    venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:8088 \
            --error-logfile ${logfile} --access-logfile ${logfile} web:app &
    web_pid="$!"
    log "web_pid=${web_pid}"
}

stop()
{
    log "stopping..."
    log "feed_pid=${feed_pid}"
    log "web_pid=${web_pid}"
    kill ${feed_pid} ${web_pid} >> ${logfile} 2>&1
}

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        log "restarting..."
        stop
        start
        ;;
    *)
        echo ${usage}
        exit ${exit_usage}
        ;;
esac

exit ${exit_success}