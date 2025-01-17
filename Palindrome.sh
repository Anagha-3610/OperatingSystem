#!/bin/bash
echo "First Parameter : $1"
echo "Second Parameter : $2"
for (( i=$1; i<=$2; i++ ))
do
	n=$i
	org=$i
	rev=0
	while [ $n -ne 0 ]
	do
		remainder=$(( $n % 10 ))
		rev=$(( $(( $rev * 10 )) + $remainder ))
		n=$(( $n / 10 ))
	done
	if [ $org -eq $rev ]
	then 
		#echo "$org is a Palindrome number in between $1 and $2"
		echo "$org"
	fi
done
