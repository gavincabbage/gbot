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

export GBOT_ROOT_DIR=/home/gbot/gbot

start()
{
    echo "Starting gbot"
    echo "TEST FILE CONTENT" > /tmp/testfile.txt
    $GBOT_ROOT_DIR/bin/gbotd.sh
}

stop()
{
    echo "Stopping gbot"
    killall $GBOT_ROOT_DIR/bin/gbotd.sh
}

case "$1" in
    start)
        start
        ;;
    stop)
        stop
        ;;
    restart)
        stop
        start
        ;;
    *)
        echo "Usage: /etc/init.d/servod start|stop"
        exit 1
        ;;
esac

exit 0