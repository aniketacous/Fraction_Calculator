CFLAGS = -c -I$(HOME)/Programming/include
LFLAGS = -L$(HOME)/Programming/lib
LIBS = -ldataStructures

project2: calculator.o dictionary.o
	g++ $(LFLAGS) -o project2 calculator.o dictionary.o $(LIBS)

calculator.o: calculator.cpp
	g++ $(CFLAGS) calculator.cpp

dictionary.o: dictionary.cc
	g++ $(CFLAGS) dictionary.cc
