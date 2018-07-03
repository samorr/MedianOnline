#include "MedianList.h"

template <typename T, typename M>
void MedianList<T, M>::insert(T v)
{
    if (firstNode == nullptr)
    {
        len = 1;
        firstNode = new Node(v);
        median = firstNode;
    }
    else
    {
        len++;
        std::size_t insertedIndex = 1;
        Node* node = firstNode;
        if (node->value >= v)
        {
            firstNode = new Node(v);
            firstNode->next = node;
            node->previous = firstNode;
        }
        else
        {
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
            if (oldNext != nullptr)
            {
                oldNext->previous = node->next;
            }
        }
        std::size_t oldMedianIndex = len / 2;
        /* there are four options, in two of them median pointer doesn't change
           so we don't have to do anything */
        if (len % 2 == 0 && insertedIndex <= oldMedianIndex)
        {
            median = median->previous;
        }
        else if (len % 2 == 1 && insertedIndex > oldMedianIndex)
        {
            median = median->next;
        }
    }

}