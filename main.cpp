#include <iostream>
#include "MedianList.h"
#include "MedianHeaps.h"


const std::string endOfStreamConst = "q";
const std::string medianRequestConst = "m";

/*
This solution usees two heaps, minHeap (minimum at the root) and maxHeap (maximum
at the root). All elements greater than median are stored in minHeap, smaller
in maxHeap. We want median to be in one of roots or average of two if we have
even number of elements. That's why we need to have balance between heaps, so
when one heap has more than one element more than the other then we have to
remove root from bigger one and insert it to smaller.
With this data structure we can check median in constant time.
Inserting new element costs us O(log n) time, where n is number of elements
in the heap.
Whole program should work in O(n * log n + m) time, where n is number of inserted
elements and m is number of median checks.
*/
void runWithMedianHeaps()
{
    MedianHeaps<int, float> heaps([](int a, int b) { return a >= b; },
                                  [](int a, int b) { return a <= b; });
    std::string input;
    std::cin >> input;
    while(input != endOfStreamConst)
    {
        if (input == medianRequestConst)
        {
            std::cout << heaps.getMedianValue() << " ";
        }
        else
        {
            heaps.insert(std::stoi(input));
        }
        std::cin >> input;
    }

}

/* 
This is much simpler solution. We store data in sorted list, so we know that
median is in the middle and we can check it in constant time. Because it's a
list we don't have direct access to elements, so we use linear time for
inserting new values.
Whole program should work in O(n^2 + m) time, where n is number of inserted
elements and m is number of median checks.
*/
void runWithMedianList()
{
    MedianList<int, float> list;
    std::string input;
    std::cin >> input;
    while(input != endOfStreamConst)
    {
        if (input == medianRequestConst)
        {
            std::cout << list.getMedianValue() << " ";
        }
        else
        {
            list.insert(std::stoi(input));
        }
        std::cin >> input;
    }
}

int main()
{
    /* This two lines are not necessary, but they can make I/O operations faster.
       First turns off synchronization between C++ and C streams. Second turns
       off automatic buffor flushing when calling std::cin. Unfortunately they
       cause memory leaks, so comment it for memory leaks testing e.g. with valgrind. */
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    runWithMedianHeaps();

    /* If you want to test also MedianList solution please use runWithMedianList
       function. */
    
    return 0;
}