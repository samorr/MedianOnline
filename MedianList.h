#ifndef MEDIAN_LIST_H
#define MEDIAN_LIST_H

#include <iostream>

template <typename T, typename M> // T is type of elements of the lists
class MedianList                  // M is type of median representation
{
public:
    class Node
    {
    public:
        T value;
        Node* next;     // in fact next pointer would be enough
        Node* previous; // but we are interested in time optimisation
                        
        // T is simple numeric type, so we only need by-value constructor
        Node(T v) : value(v), next(nullptr), previous(nullptr) {}
        
        // we delete only next Node, previous one need to still exist
        ~Node() noexcept
        {
            delete next;
        }

    };

    Node* firstNode;
    Node* median;
    std::size_t len;

    MedianList() : firstNode(nullptr), median(nullptr), len(0) {}
    ~MedianList() noexcept
    {
        delete firstNode;
    }

    friend std::ostream& operator << (std::ostream &out, const MedianList<T, M>& list)
    {
        Node* node = list.firstNode;
        for (std::size_t i = 0; i < list.len; i++)
        {
            out << node->value << " ";
            node = node->next;
        }
        return out;
    }
    
    void insert(T v);
    M getMedianValue() const
    {
        return len % 2 == 1 ? 
                static_cast<M>(median->value) : 
                (static_cast<M>(median->value) + static_cast<M>(median->next->value)) / static_cast<M>(2);
    }

};

#endif