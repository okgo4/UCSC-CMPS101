#------------------------------------------------------------------------------

# Makefile for CMPS 101-01 Programming Assignment 3#

#       make                   makes DigraphProperties
#------------------------------------------------------------------------------

#Roy Wang #1636195 hwang167 PA3#
################################
DigraphProperties : DigraphProperties.o List.o Digraph.o

	gcc -o DigraphProperties DigraphProperties.o List.o Digraph.o


DigraphProperties.o : DigraphProperties.c List.h Digraph.h

	gcc -c -std=c99 -Wall DigraphProperties.c


List.o : List.c List.h

	gcc -c -std=c99 -Wall List.c


Digraph.o : Digraph.c Digraph.h

	gcc -c -std=c99 -Wall Digraph.c

clean :

	rm -f DigraphProperties DigraphProperties.o List.o Digraph.o
 
