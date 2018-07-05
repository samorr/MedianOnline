#include "MedianHeaps.h"

template <typename T, typename M>
void MedianHeaps<T,M>::insert(T v)
{
    if (maxHeap.size == 0)
    {
        /* If maxHeap is empty then minHeap has at most one element,
           so we can insert to minHeap and balance heaps later. */
        minHeap.insert(v);
    }
    else if (maxHeap.compare(maxHeap.getRootValue(), v))
    {
        maxHeap.insert(v);
    }
    else
    {
        minHeap.insert(v);
    }

    /* There cannot be more difference than 2. */
    if (minHeap.size - maxHeap.size == 2)
    {
        T value = minHeap.removeRoot();
        maxHeap.insert(value);
    }
    else if (maxHeap.size - minHeap.size == 2)
    {
        T value = maxHeap.removeRoot();
        minHeap.insert(value);
    }
}