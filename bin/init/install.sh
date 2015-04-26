#!/bin/bash

# Install gbot init script in /etc/init.d

GBOT_ROOT_DIR=/home/gbot/gbot
GBOT_INIT=$GBOT_ROOT_DIR/bin/init
INIT_DIR=/etc/init.d

mv $GBOT_INIT/gbot.sh $INIT_DIR/gbot

chmod 777 $INIT_DIR/gbot

update-rc.d $INIT_DIR/gbot defaults

