all: run-conway

run-conway: ConwayGrid.o ConwayMain.o
	g++ -g -std=c++17 ConwayGrid.o ConwayMain.o -o run-conway.o

ConwayGrid.o: ConwayGrid.cpp GridElement.h
	g++ -std=c++17 -c ConwayGrid.cpp -o ConwayGrid.o

ConwayMain.o: ConwayMain.cpp
	g++ -std=c++17 -c ConwayMain.cpp -o ConwayMain.o

clean:
	rm *.o