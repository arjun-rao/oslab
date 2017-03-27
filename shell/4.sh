#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: 4.sh <user1> <user2> ..."
    exit
else
    for user in $*
    do        
        if [ -d $(eval echo ~$user) ]; then
            eval echo ~$user
        else
            echo "Invalid user $user"
        fi
    done
fi