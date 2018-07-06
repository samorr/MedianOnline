Flags = -Wall -Werror -std=c++17 # use also -g flag for debugging
CPP = g++

main : Makefile main.o templates.o MedianList.o MedianHeaps.o
	$(CPP) $(Flags) MedianList.o MedianHeaps.o templates.o main.o -o main

main.o : Makefile main.cpp MedianList.h MedianHeaps.h
	$(CPP) -c $(Flags) main.cpp -o main.o

templates.o : Makefile templates.cpp MedianList.h SimpleHeap.h MedianHeaps.h MedianList.cpp SimpleHeap.cpp MedianHeaps.cpp
	$(CPP) -c $(Flags) templates.cpp -o templates.o

MedianList.o : Makefile MedianList.h MedianList.cpp
	$(CPP) -c $(Flags) MedianList.cpp -o MedianList.o

MedianHeaps.o : Makefile MedianHeaps.h MedianHeaps.cpp SimpleHeap.h
	$(CPP) -c $(Flags) MedianHeaps.cpp -o MedianHeaps.o

SimpleHeap.o : Makefile SimpleHeap.h SimpleHeap.cpp
	$(CPP) -c $(Flags) SimpleHeap.cpp -o SimpleHeap.o

runtest : Makefile main test_in test_out
	./main < test_in > prog_out
	cmp --silent prog_out test_out && echo -e '\n\n### SUCCESS: Well done! ###' || echo -e '\n\n### ERROR: Some bad answer! ###'

# For test generating you will need python with numpy
# If you don't have, you can use test generated before
test_in test_out : Makefile testsGenerator.py
	python testsGenerator.py

clean :
	$(RM) MedianHeaps.o SimpleHeap.o MedianList.o templates.o main.o main