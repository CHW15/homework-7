all: golnaz

golnaz: earthquake.o station.o golnaz.o 
	g++ -o golnaz earthquake.o station.o golnaz.o
	
earthquake.o: earthquake.cpp
	g++ -c earthquake.cpp
	
station.o: station.cpp
	g++ -c station.cpp	
	
clean:
	rm golnaz *.o