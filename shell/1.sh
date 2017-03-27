#!/bin/bash
if [ $# -eq 0 ]; then
    echo "Not enough arguments"
    exit
else
   for s in $@
   do
     str="$s $str"
   done
   echo $str
fi