# Makefile for golnaz.cpp

CC = g++

# Flags to the compiler

CFLAGS = 

all: golnaz

golnaz: golnaz.o mutualfunctions.o earthquake.o station.o LNK2005errorpass.o 
	g++ -o golnaz golnaz.o mutualfunctions.o earthquake.o station.o LNK2005errorpass.o

golnaz.o: golnaz.cpp
	${CC} -c golnaz.cpp

myFunction.o: myFunction.cpp
	${CC} -c myFunction.cpp

LNK2005errorpass.o: LNK2005errorpass.cpp
	${CC} -c LNK2005errorpass.cpp

station.o: station.cpp
	${CC} -c station.cpp 

clean:
	rm -rf *.o