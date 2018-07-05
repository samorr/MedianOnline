#include <iostream>
#include "MedianList.h"
#include "MedianHeaps.h"
#include "SimpleHeap.h"


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

    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    MedianHeaps<int, float> heaps([](int a, int b) { return a >= b; },
                                  [](int a, int b) { return a <= b; });
    std::string input;
    std::cin >> input;
    while(input != "q")
    {
        if (input == "m")
        {
            std::cout << heaps.getMedianValue() << " ";
        }
        else
        {
            heaps.insert(std::stoi(input));
        }
        std::cin >> input;
    }

    return 0;
}