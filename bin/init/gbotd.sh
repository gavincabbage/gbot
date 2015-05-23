#! /bin/sh

### BEGIN INIT INFO
# Provides:          gbotd
# Required-Start:    $local_fs $remote_fs $syslog $network $time $redis-server $nginx
# Required-Stop:     $local_fs $remote_fs $syslog $network $time $redis-server $nginx
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: gbotd initscript
# Description:       This file should be named to 'gbotd' placed in /etc/init.d.
### END INIT INFO

export GBOT_ROOT_DIR="/home/gbot/gbot"

usage="Usage: /etc/init.d/servod start|stop|restart"
initfile=`basename "$0"`
logfile="/tmp/gbotd_log.txt"

exit_success=0
exit_usage=1

log()
{
    echo ${initfile}": $1" >> ${logfile} 2>&1
}

start()
{
    cd ${GBOT_ROOT_DIR}
    ./bin/startup.sh
}

stop()
{
    log "stopping..."
    feed_pid=`redis-cli -p 8090 -n 0 get feed_pid` >> ${logfile} 2>&1
    web_pid=`redis-cli -p 8090 -n 0 get web_pid` >> ${logfile} 2>&1
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