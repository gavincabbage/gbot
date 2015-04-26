#! /bin/sh

### BEGIN INIT INFO
# Provides:          gbot
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
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

gbot_init_logfile="/tmp/gbot_init_log.txt"

log()
{
    echo "$1" >> ${gbot_init_logfile} 2>&1
}

start()
{
    log ${gbot_init_logfile}": start"
    ${GBOT_ROOT_DIR}/bin/gbotd.sh >> ${gbot_init_logfile} 2>&1
}

stop()
{
    log ${gbot_init_logfile}": stop"
    killall gbotd.sh >> ${gbot_init_logfile} 2>&1
    killall gunicorn
}

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        log ${gbot_init_logfile}": restart"
        stop
        start
        ;;
    *)
        echo ${usage}
        exit 1
        ;;
esac

exit ${exit_success}