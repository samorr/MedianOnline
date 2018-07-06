#include "MedianList.h"

template <typename T, typename M>
void MedianList<T, M>::insert(T v)
{
    /* If list is empty we just have to add first element and end here.
       Then this element is the median also. */
    if (firstNode == nullptr)
    {
        len = 1;
        firstNode = new Node(v);
        median = firstNode;
        return;
    }
    /* Else we need to find right place for new element. */
    len++;
    /* We have to remember where we inserted new element to know how change
       median pointer. */
    std::size_t insertedIndex = 1;
    Node* node = firstNode;
    if (node->value >= v)
    {
        /* If new value is smaller than first element it means that it should
           be new first element. */
        firstNode = new Node(v);
        firstNode->next = node;
        node->previous = firstNode;
    }
    else
    {
        /* Else we iterate untill we find right place. */
        insertedIndex = 2;
        while (node->next != nullptr && node->next->value < v)
        {
            node = node->next;
            insertedIndex++;
        }
        Node* oldNext = node->next;
        node->next = new Node(v);
        node->next->next = oldNext;
        node->next->previous = node;
        /* When we add new element somewhere in the middle of the list, then
           we have to take care of element behind it. */
        if (oldNext != nullptr)
        {
            oldNext->previous = node->next;
        }
    }
    std::size_t oldMedianIndex = len / 2;
    /* There are four options, in two of them median pointer doesn't change
        so we don't have to do anything. */
    if (len % 2 == 0 && insertedIndex <= oldMedianIndex)
    {
        median = median->previous;
    }
    else if (len % 2 == 1 && insertedIndex > oldMedianIndex)
    {
        median = median->next;
    }
}