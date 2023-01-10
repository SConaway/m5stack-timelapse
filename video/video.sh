#! /usr/bin/env bash

# set failure
set -e

# cd to the directory of this script
cd "$(dirname "$0")"

# call timestamp.js
node timestamp.js

# call ffmpeg script
./ffmpeg.sh

# print video file size in MB
ls -l ../images/video.mp4 | awk '{print $5/1000000}' | xargs -I {} echo "Video file size: {} MB"
