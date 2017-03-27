#!/bin/bash

function max_size {    

    if [ ! -d $1 ]; then
        echo "Invalid Directory"
        exit
    fi

    max=0
    for f in $(find $1 -type f)
    do
        fsize=$(stat -f%z $f) #in linux use $(stat -c %s $f)
        if [ $fsize -ge $max ]; then
            max=$fsize
            maxf=$f
        fi
    done
    echo "$maxf : $max "
}

read -p "Parent Dir:" dir
max_size $dir