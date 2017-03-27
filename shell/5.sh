#!/bin/bash

echo "Enter the password: "
read -s pass1
echo "Confirm the password: "
read -s pass2

if [ $pass1 = $pass2 ]
	then
	echo "The terminal is locked!"
	trap '' 2 3 15
	while true
	do
		echo "Enter the password: "
		read -s pass3
		if [ $pass3 = $pass2 ]
			then
			echo "The terminal is unlocked!"			
			exit
		else
			echo "Incorrect password! Try again."
		fi
	done
else
	echo "Passwords do not match!"	
fi
