#!/bin/bash

# Install gbot init script in /etc/init.d

GBOT_ROOT_DIR=/home/gbot/gbot
GBOT_INIT=$GBOT_ROOT_DIR/bin/init
INIT_DIR=/etc/init.d

cp $GBOT_INIT/gbotd.sh $INIT_DIR/gbotd

chmod 777 $INIT_DIR/gbotd

update-rc.d gbotd defaults