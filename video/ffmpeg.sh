#! /usr/bin/env bash

# Set the input and output directories
input_dir='../images/ts'
# temp_file='../images/temp.mp4'
output_file='../images/video.mp4'

# Set the output video dimensions and frame rate
width='1280'
height='1024'
framerate='30' # images per second

final_fr='30' # final frame rate
[ $framerate -gt 30 ] && final_fr='60'

# read the number of zeros to use for the image file names, e.g. 0001.jpg
num_zeros=$(ls -1 $input_dir | head -n 1 | grep -o '[0-9]\+' | tr -d '\n' | wc -m | xargs)

# echo "$input_dir/%$num_zeros"d.jpg

# Create a temp video file using ffmpeg
ffmpeg -y -framerate $framerate -pattern_type glob -i "$input_dir/*.jpg" -c:v libx264 -crf 24 -preset fast -pix_fmt yuv420p -vf "scale=$width:$height" -filter:v fps=$final_fr $output_file
# ffmpeg -y -framerate $framerate -i "$input_dir/%0$num_zeros"d.jpg -c:v libx264 -pix_fmt yuv420p -vf "scale=$width:$height" $temp_file
# ffmpeg -y -pattern_type glob -i "$input_dir/*.jpg" -c:v libx264 -pix_fmt yuv420p -vf "scale=$width:$height" -r $framerate $temp_file

# # change the frame rate to 30fps for easier viewing
# ffmpeg -i $temp_file -r 30 $output_file

# remove input directory
# rm -rf $input_dir
