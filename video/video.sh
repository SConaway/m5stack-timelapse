#! /usr/bin/env bash

# set failure
set -e

# call timestamp.js
node timestamp.js

# call ffmpeg script
./ffmpeg.sh

# print video file size
ls -l ../images/video.mp4 | awk '{print $5}'
