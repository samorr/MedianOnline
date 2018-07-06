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
    /* cmpMax and cmpMin should define linear order on elements of type T
       in such way, that they can be used in maxHeap and minHeap respectively.
       E.g. cmpMax = '>=' and cmpMin = '<='. */
    MedianHeaps(bool (* cmpMax)(T, T), bool (* cmpMin)(T, T))
        : maxHeap(cmpMax), minHeap(cmpMin)
    { }

    void insert(T v);
    M getMedianValue()
    {
        return maxHeap.size == minHeap.size ?
                /* If heaps have the same size we return average of their roots. */
                static_cast<M>(maxHeap.getRootValue() + minHeap.getRootValue())
                    / static_cast<M>(2) :
                /* Else we return value of root from heap with greater size. */
                maxHeap.size < minHeap.size ?
                    static_cast<M>(minHeap.getRootValue()) :
                    static_cast<M>(maxHeap.getRootValue());
    }
};

#endif