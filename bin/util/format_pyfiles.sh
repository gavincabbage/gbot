#!/bin/bash

AUTOPEP8=$GBOT_ROOT_DIR/venv/bin/autopep8

cd $GBOT_ROOT_DIR/feed
$AUTOPEP8 *.py --in-place --recursive

cd ../web
$AUTOPEP8 *.py --in-place --recursive

cd ../externals
$AUTOPEP8 *.py --in-place --recursive