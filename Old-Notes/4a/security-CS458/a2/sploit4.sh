#!/bin/bash          

url=$1'/post.php'

curl -c cookies.txt $url --data 'username=j3tracey&password=j3tracey&form=login&submit=Login' 

echo "Just logged in as j3tracy"

# comment
curl -b cookies.txt $url --data 'comment=Hello+there%2C+I+am+definitely+not+tracy&form=comment&parent=2&submit=Post'

echo "Just commented on \"How to use submit\" as j3tracy"
