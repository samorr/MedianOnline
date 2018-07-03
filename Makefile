Flags = -Wall -Werror -std=c++11 # use also -g flag for debugging
CPP = g++

main : Makefile MedianList.o main.o templates.o
	$(CPP) $(Flags) MedianList.o templates.o main.o -o main

main.o : Makefile main.cpp MedianList.h
	$(CPP) -c $(Flags) main.cpp -o main.o

templates.o : Makefile MedianList.o templates.cpp
	$(CPP) -c $(Flags) templates.cpp -o templates.o

MedianList.o : Makefile MedianList.h MedianList.cpp
	$(CPP) -c $(Flags) MedianList.cpp -o MedianList.o

clean :
	$(RM) MedianList.o templates.o main.o main