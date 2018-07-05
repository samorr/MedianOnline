#include <iostream>
#include "MedianList.h"
#include "SimpleHeap.h"

template class MedianList<int, float>;

int main()
{
    // std::ios::sync_with_stdio(false);
    // std::cin.tie(NULL);
    
    // MedianList<int, float> list;
    // std::string input;
    // std::cin >> input;
    // while(input != "q")
    // {
    //     // std::cout << input;
    //     if (input == "m")
    //     {
    //         std::cout << list.getMedianValue() << " ";
    //     }
    //     else
    //     {
    //         list.insert(std::stoi(input));
    //     }
    //     std::cin >> input;
    // }

    SimpleHeap<int, float> heap([](int a, int b) { return a <= b; });
    heap.insert(10);
    heap.insert(5);
    heap.insert(20);
    std::cout << heap.removeRoot() << "\n";
    heap.insert(10);
    heap.insert(1);
    heap.insert(4);
    std::cout << heap.removeRoot() << "\n";


    return 0;
}