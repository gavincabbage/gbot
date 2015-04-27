#! /bin/sh

### BEGIN INIT INFO
# Provides:          gbotd
# Required-Start:    $local_fs $remote_fs $syslog $network $time
# Required-Stop:     $local_fs $remote_fs $syslog $network $time
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: gbot initscript
# Description:       This file should be named to 'gbot' placed in /etc/init.d.
### END INIT INFO

export GBOT_ROOT_DIR="/home/gbot/gbot"

usage="Usage: /etc/init.d/servod start|stop|restart"
initfile="/etc/init.d/gbot"
gbot_logfile="/tmp/gbot_log.txt"
exit_success=0
exit_usage=1

log()
{
    echo ${initfile}": $1" >> ${gbot_logfile} 2>&1
}

start()
{
    log "starting..."
    cd ${GBOT_ROOT_DIR}
    venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:8088 \
            --error-logfile ${gbot_logfile} --access-logfile ${gbot_logfile} web:app &
}

stop()
{
    log "stopping..."
    killall gunicorn >> ${gbot_logfile} 2>&1
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