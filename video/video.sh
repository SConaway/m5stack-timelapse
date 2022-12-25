#! /usr/bin/env bash

# set failure
set -e

# call timestamp.js
node timestamp.js

# call ffmpeg script
./ffmpeg.sh
