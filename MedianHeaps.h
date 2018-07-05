#ifndef MEDIAN_HEAPS_H
#define MEDIAN_HEAPS_H 1

#include "SimpleHeap.h"

/* T is type of elements of the heaps
   M is type of median representation */
template <typename T, typename M>
class MedianHeaps
{
private:
    SimpleHeap<T> maxHeap, minHeap;

public:
    MedianHeaps(bool (* cmpMax)(T, T), bool (* cmpMin)(T, T))
        : maxHeap(cmpMax), minHeap(cmpMin)
    { }

    void insert(T v);
    M getMedianValue()
    {
        return maxHeap.size == minHeap.size ?
                static_cast<M>(maxHeap.getRootValue() + minHeap.getRootValue())
                    / static_cast<M>(2) :
                maxHeap.size < minHeap.size ?
                    static_cast<M>(minHeap.getRootValue()) :
                    static_cast<M>(maxHeap.getRootValue());
    }
};

#endif