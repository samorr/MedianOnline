#include "MedianHeaps.h"

template <typename T, typename M>
void MedianHeaps<T,M>::insert(T v)
{
    if (maxHeap.size == 0)
    {
        /* If maxHeap is empty then minHeap has at most one element,
           so we can insert to minHeap and balance heaps later if necessary. */
        minHeap.insert(v);
    }
    else if (maxHeap.compare(maxHeap.getRootValue(), v))
    {
        /* If inserted element is smaller than root of maxHeap, then we should
           add it to maxHeap. */
        maxHeap.insert(v);
    }
    else
    {
        /* Else it is greater than maxHeap root so it should be inserted in minHeap. */
        minHeap.insert(v);
    }
    /* If heaps differ in sizes by more than one, then we should balance them.
       It means removing root from greater and insert it to smaller. */
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