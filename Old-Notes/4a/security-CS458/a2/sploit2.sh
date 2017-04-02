#!/bin/bash          

url=$1'/post.php'

curl -c cookies.txt $url --data 'username=nasghar&password=weERKDekj4&form=login&submit=Login'

echo "Just logged in as nasghar"

curl -b cookies.txt $url --data 'title=This+is+a+link&content=http%3A%2F%2Fzeldawiki.org%2FLink&type=2&form=content&submit=Post'

echo "Just posted a link as nasghar"