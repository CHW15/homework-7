# Makefile for golnaz.cpp

CC = g++

# Flags to the compiler

CFLAGS = 

all: golnaz

golnaz: golnaz.o mutualfunctions.o earthquake.o station.o 
	g++ -o golnaz golnaz.o mutualfunctions.o earthquake.o station.o 

golnaz.o: golnaz.cpp
	${CC} -c golnaz.cpp

myFunction.o: myFunction.cpp
	${CC} -c myFunction.cpp

station.o: station.cpp
	${CC} -c station.cpp 

clean:
	rm -rf *.o