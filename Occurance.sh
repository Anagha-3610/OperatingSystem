#!/bin/bash
value=$(<TEXT1.txt)
echo "$value"
echo "Enter word to be searched"
read occ
count=0
while read sentence
do
	for word in $sentence; 
	do
		if [ "$occ" == "$word" ]
		then
        		count=$(( $count + 1 ))
		fi
	done
done < "TEXT1.txt"
echo "Occurance of '$occ' is: $count"
