#!/bin/bash

read -p "Enter String:" str
str=$(echo $str | rev)
echo $str