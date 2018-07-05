/*
This file exists only to explicitly instantiate every use of MedianList
template class
*/

#include "MedianList.h"
#include "MedianList.cpp"
#include "SimpleHeap.h"
#include "SimpleHeap.cpp"
#include "MedianHeaps.h"
#include "MedianHeaps.cpp"

template class MedianList<int, float>;
template class SimpleHeap<int>;
template class MedianHeaps<int, float>;