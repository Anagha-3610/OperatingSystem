#!/bin/bash
Choice=1
while [ "$Choice" -eq "1" ]
do
echo "Enter your option"
echo "1)Addition" 
echo "2)Subtraction"
echo "3)Multiplication"
echo "4)Division"
echo "5)Modulus"
read option
if [ "$option" = "1" ]
then
	echo "Enter 1st element" 
	read num1
	echo "Enter 2nd element" 
	read num2
	sum=$(( $num1 + $num2 ))
	echo "Sum is :$sum"
elif [ "$option" = "2" ]
then
        echo "Enter 1st element"
        read num1
        echo "Enter 2nd element"
        read num2
        diff=$(( $num1 - $num2 ))
        echo "Difference is :$diff"
elif [ "$option" = "3" ]
then
        echo "Enter 1st element"
        read num1
        echo "Enter 2nd element"
        read num2
        prd=$(( $num1 * $num2 ))
        echo "Product is :$prd"
elif [ "$option" = "4" ]
then
        echo "Enter 1st element"
        read num1
        echo "Enter 2nd element"
        read num2
        div=$(( $num1 / $num2 ))
        echo "Quotient is :$div"
elif [ "$option" = "5" ]
then
        echo "Enter 1st element"
        read num1
        echo "Enter 2nd element"
        read num2
        mod=$(( $num1 % $num2 ))
        echo "Modulus is :$mod"
else
	echo "Exiting"
fi
echo "DO YOU WANT TO CONTINUE THE ARITHMETIC OPERATIONS"
read Choice
if [ "$Choice" != "1" ]
then
        echo "THE OPERATIONS ARE ENDED"
fi
done
