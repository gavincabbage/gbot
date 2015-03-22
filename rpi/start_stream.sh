#!/bin/bash

sudo raspivid -n -ih -t 0 -ISO 800 -ex night -w 720 -h 405 -fps 25 -b 20000000 -o - | \
sudo ffmpeg -y \
	-loglevel panic \
	-i - \
	-c:v copy \
	-map 0 \
	-f ssegment \
	-segment_time 1 \
	-segment_format mpegts \
	-segment_list "$base/stream.m3u8" \
	-segment_list_size 10 \
	-segment_wrap 20 \
	-segment_list_flags +live \
	-segment_list_type m3u8 \
	-segment_list_entry_prefix /cam/segments/ \
	"$base/segments/%03d.ts"
