#! /bin/sh

### BEGIN INIT INFO
# Provides:          gbot
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
exit_success=0
exit_usage=1

gbot_logfile="/tmp/gbot_log.txt"

log()
{
    echo ${gbot_logfile}": $1" >> ${gbot_logfile} 2>&1
}

start()
{
    log "starting..."
    cd ${GBOT_ROOT_DIR}
    venv/bin/gunicorn --timeout 3600 -w 2 -b 0.0.0.0:8088 --error-logfile - --access-logfile - web:app >> ${gbot_logfile} 2>&1 &

}

stop()
{
    log "stopping..."
    killall gbotd.sh >> ${gbot_logfile} 2>&1
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
        exit 1
        ;;
esac

exit ${exit_success}