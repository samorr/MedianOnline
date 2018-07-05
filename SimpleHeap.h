#ifndef SIMPLE_HEAP_H
#define SIMPLE_HEAP_H 1

#include <iostream>
#include <stdexcept>

/* Class is named SimpleHeap, because it doesn't have all heap functionality */
template <typename T> 
class SimpleHeap
{
private:
    // This class represents elements of the SimpleHeap
    class Node
    {
    public:
        T value;

        /* We can't implement heap in an array because we want to be able
           to increase its size effectively. That's why we need pointers. */
        Node* father;
        Node* leftSon;
        Node* rightSon;

        /* Created Node doesn't know its father and sons, caller should take care
        of those pointers later */
        Node(T v)
            : value(v), father(nullptr), leftSon(nullptr), rightSon(nullptr) {}
        
        ~Node() noexcept
        {
            /* we only have two remove sons, father should exist still*/
            delete leftSon;
            delete rightSon;
        }
    };

    Node* root;

    /* This is very generic function. Getting first free pointer and removing
       last node are very similar operations, because we have to move around
       the heap in the same way. Only last operations are different, so by
       boolean arguments we can say if we want to add or remove node. */
    auto getNodeToAddOrRemove(std::size_t way, bool remove, bool add, T v);

    /* Restore order in the heap starting from *node, moving it up or down. */
    void restoreOrderUp(Node* node);
    void restoreOrderDown(Node* node);

    /* We need to implement swap ourselves to not use algorithm library */
    void swapValues(T& v1, T& v2)
    {
        T temp = std::move(v1);
        v1 = std::move(v2);
        v2 = std::move(temp);
    }

public:
    std::size_t size;

    /* This is pointer to function which should compare values of Nodes, 
       to define linear order on them. With different compare functions
       we can make different heaps (e.g. min or max heaps). */
    bool (* compare)(T, T);

    SimpleHeap(bool (* cmp)(T, T)) : root(nullptr), size(0), compare(cmp) {}
    ~SimpleHeap() noexcept
    {
        /* We only have to delete root,
           other Nodes should be removed recursively */
        delete root;
    }

    void insert(T v);

    /* Remove root and return its value after order restoring */
    T removeRoot();

    T getRootValue() const
    {
        if (size == 0)
        {
            throw std::invalid_argument("Attempt to get root value from empty heap!");
        }
        return root->value;
    }

};


#endif