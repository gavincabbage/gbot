#!/bin/bash

# Install gbotd init script in /etc/init.d

GBOT_ROOT_DIR=/home/gbot/gbot
GBOT_INIT=$GBOT_ROOT_DIR/bin/init
INIT_DIR=/etc/init.d

cp $GBOT_INIT/gbotd.sh $INIT_DIR/gbotd

chmod 777 $INIT_DIR/gbotd

# Install redis config.

sudo cp $GBOT_ROOT_DIR/config/redis.conf /etc/redis/redis.conf

# Set gbotd and redis to start on boot.

update-rc.d gbotd defaults
update-rc.d redis-server defaults