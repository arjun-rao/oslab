#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Give 3 numbers as args"
    exit
fi

if [ $1 -gt $2 ] && [ $1 -gt $3 ]
then
    echo "Max: $1"
elif [ $2 -gt $1 ] && [ $2 -gt $3 ]
then
    echo "Max: $2"
else
    echo "Max: $3"
fi