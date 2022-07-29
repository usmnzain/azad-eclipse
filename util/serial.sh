#!/bin/bash

code="/home/usman/Documents/eclipse-embed-workspace/azadi-debug/Debug/azadi-debug.hex"
while read -r ins; do
    hex=($(sed 's/../\\x& /g' <<< $ins))
    echo "${hex[0]}${hex[1]}${hex[2]}${hex[3]}"
done < "$code"
#echo -en '\x00\x00\x0f\xff' > /dev/ttyUSB1
#echo -en '\x00\x00\x0f\xff' > /dev/ttyUSB1
#echo -en '\x00\x00\x0f\xff' > /dev/ttyUSB1 
