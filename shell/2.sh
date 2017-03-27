#!/bin/bash

if [ $# -ne 2 ]; then
    echo "usage: 2.sh <file1> <file2>"
    exit
else
    f1=$(ls -l $1 | cut -c2-10)
    f2=$(ls -l $2 | cut -c2-10)
    if [ $f1 == $f2 ]; then
        echo "Permissions are same, $f1"
    else
        echo "Permissions of $1: $f1"
        echo "Permissions of $2: $f2"
        exit
    fi

fi