##############################################
# Author: Samuel Lamb												 #
# Class: cop4530                             #
# Assignment: Assignemnt 4                   # 
# Filename: makefile                         #
# Date Created: 3/1/2020                     #
# Description: makefile for assignment 4     #
##############################################

CC= g++ -g -std=c++11 -Wall -Wextra -I. -o

main: proj4.x

proj4.x: proj4_driver.cpp bet.hpp bet.h
			$(CC) proj4.x proj4_driver.cpp

clean: 
		-rm *.o
		-rm *.h.gch
		-rm *.x