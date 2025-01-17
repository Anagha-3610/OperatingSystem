#!/bin/bash
echo "Enter the limit of fibonacci series"
read limit
el1=0
el2=1
count=3
echo $el1
echo $el2
while [ $count -le $limit ]
do
	el3=$(( $el1 + $el2 ))
	#if [ $el3 -lt $limit ]
        #then
	echo $el3
        #fi
	el1=$el2
	el2=$el3
	count=$(( $count + 1 ))
done
