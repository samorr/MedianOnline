Flags = -Wall -Werror -std=c++17 -g # use also -g flag for debugging
CPP = g++

main : Makefile main.o templates.o MedianList.o MedianHeaps.o
	$(CPP) $(Flags) MedianList.o MedianHeaps.o templates.o main.o -o main

main.o : Makefile main.cpp MedianList.h MedianHeaps.h
	$(CPP) -c $(Flags) main.cpp -o main.o

templates.o : Makefile templates.cpp MedianList.h SimpleHeap.h MedianHeaps.h
	$(CPP) -c $(Flags) templates.cpp -o templates.o

MedianList.o : Makefile MedianList.h MedianList.cpp
	$(CPP) -c $(Flags) MedianList.cpp -o MedianList.o

MedianHeaps.o : Makefile MedianHeaps.h MedianHeaps.cpp SimpleHeap.h
	$(CPP) -c $(Flags) MedianHeaps.cpp -o MedianHeaps.o

SimpleHeap.o : Makefile SimpleHeap.h SimpleHeap.cpp
	$(CPP) -c $(Flags) SimpleHeap.cpp -o SimpleHeap.o

clean :
	$(RM) MedianList.o templates.o main.o main