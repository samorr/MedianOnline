Flags = -Wall -Werror -std=c++17 -g # use also -g flag for debugging
CPP = g++

main : Makefile main.o templates.o MedianList.o SimpleHeap.o
	$(CPP) $(Flags) MedianList.o templates.o main.o -o main

main.o : Makefile main.cpp MedianList.h SimpleHeap.h
	$(CPP) -c $(Flags) main.cpp -o main.o

templates.o : Makefile templates.cpp MedianList.o SimpleHeap.o
	$(CPP) -c $(Flags) templates.cpp -o templates.o

MedianList.o : Makefile MedianList.h MedianList.cpp
	$(CPP) -c $(Flags) MedianList.cpp -o MedianList.o

SimpleHeap.o : Makefile SimpleHeap.h SimpleHeap.cpp
	$(CPP) -c $(Flags) SimpleHeap.cpp -o SimpleHeap.o

clean :
	$(RM) MedianList.o templates.o main.o main