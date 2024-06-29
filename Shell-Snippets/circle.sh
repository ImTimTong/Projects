# Name: Timothy Tong
# Date: 4/3/2024
# Title: Lab1 - 3
# Description: This program computes the area and perimeter of a circle given user input for radius. It exits with error code if radius input is less than 0.

#!/bin/sh

#This function computes the area of a circle using bc given radius input ($1) and prints to stdout
area () {
    echo "3.14 * $1 * $1"|bc
}

#This function computes the perimeter of a circle using bc given radius input ($1) and prints to stdout
perimeter () {
    echo "2 * 3.14 * $1"|bc
}

#Read user input into radius variable, and check if value is positive. If so, print out area and perimeter. Otherwise, exit with error code.
echo "Enter radius of circle:"
read radius
if [ $radius -lt 0 ]
then
    echo "Not a positive number!"
    exit 1
fi
echo "The area of the circle is `area $radius`" #two ways to capture function output
echo "The perimeter of the circle is $(perimeter $radius)"
