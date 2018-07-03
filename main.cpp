#include <iostream>
#include "MedianList.h"

template class MedianList<int, float>;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    
    MedianList<int, float> list;
    std::string input;
    std::cin >> input;
    while(input != "q")
    {
        // std::cout << input;
        if (input == "m")
        {
            std::cout << list.getMedianValue() << " ";
        }
        else
        {
            list.insert(std::stoi(input));
        }
        std::cin >> input;
    }
    return 0;
}