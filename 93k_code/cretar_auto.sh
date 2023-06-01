#!/bin/bash

# var=$(date +"%FORMAT_STRING")
# now=$(date +"%m_%d_%Y")
# printf "%s\n" $now
# today=$(date +"%Y-%m-%d")
# printf "Today we are going to backup file to NFS server at AWS '%s'\n" "/efs/my-blog-${today}.sql.tar.gz"

DIR="backup"
if [ -d "$DIR" ]; then
   echo "'$DIR' found and now moving files, please wait ..."
   mv Digital_Training-*.tar.gz "$DIR"
else
   echo "Warning: '$DIR' NOT found. making ..."
   mkdir "$DIR"
fi

date_time=$(date +"%Y-%m-%d-%H-%M-%S")
rm Digital_Training.tar.gz
#rm -rf Digital_Training
tar -czf Digital_Training-${date_time}.tar.gz ./Digital_Training
echo "tar ..."
cp Digital_Training-${date_time}.tar.gz Digital_Training.tar.gz
echo "finish!"

