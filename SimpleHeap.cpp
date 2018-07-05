#include "SimpleHeap.h"

template <typename T, typename M>
auto SimpleHeap<T,M>::getFirstFreePointer(T v)
{
    return getNodeToAddOrRemove(size+1, false, true, v);
}

template <typename T, typename M>
auto SimpleHeap<T,M>::removeLastNode()
{
    return getNodeToAddOrRemove(size, true, false, T());
}

template <typename T, typename M>
auto SimpleHeap<T,M>::getNodeToAddOrRemove
    (std::size_t way, bool remove, bool add, T v)
{
    auto nodePointer = root;
    /* This situation shouldn't happen with normal usage of this method. */
    if (way == 1)
    {
        std::cout << "Error!\n";
        return root;
    }
    /* We can find way to first free pointer with reversed binary notation
       of heap size. */
    // std::size_t way = size;
    std::size_t binaryMask = 1;
    while(binaryMask < way)
    {
        binaryMask <<= 1;
        binaryMask++;
    }
    binaryMask >>= 1;
    way &= binaryMask;
    while(true)
    {
        binaryMask >>= 1;
        /* Check if most significant bit in way is 0 or 1. If 0 we should take
           left son, else right son. */
        if (binaryMask == 0)
        {
            if (way == 0)
            {
                auto returnNode = (nodePointer)->leftSon;
                if (remove)
                {
                    (returnNode)->father = nullptr;
                    (nodePointer)->leftSon = nullptr;
                }
                else if (add)
                {
                    returnNode = new SimpleHeap<T,M>::Node(v);
                    (nodePointer)->leftSon = returnNode;
                    (returnNode)->father = nodePointer;
                }
                return returnNode;
            }
            auto returnNode = (nodePointer)->rightSon;
            if (remove)
            {
                (returnNode)->father = nullptr;
                (nodePointer)->rightSon = nullptr;
            }
            else if (add)
            {
                returnNode = new SimpleHeap<T,M>::Node(v);
                (nodePointer)->rightSon = returnNode;
                (returnNode)->father = nodePointer;
            }
            return returnNode;
        }
        nodePointer = (way & ~binaryMask) == 0 ?
                                (nodePointer)->leftSon :
                                (nodePointer)->rightSon;
        way &= binaryMask;
    }
}

template <typename T, typename M>
T SimpleHeap<T,M>::removeRoot()
{
    T value = root->value;
    if (size == 1)
    {
        delete root;
        root = nullptr;
        return value;
    }
    auto lastNode = removeLastNode();
    (lastNode)->leftSon = root->leftSon;
    (lastNode)->rightSon = root->rightSon;
    if (root->leftSon != nullptr)
    {
        root->leftSon->father = lastNode;
        if (root->rightSon != nullptr)
        {
            root->rightSon->father = lastNode;
        }
    }
    size--;
    /* We need to set sons of old root to nullptr for destructor to done well */
    root->leftSon = nullptr;
    root->rightSon = nullptr;
    delete root;
    root = lastNode;
    /* When we restore order from root it is obvious that it should be
       restoreOrderDown. */
    restoreOrderDown(root);
    return value;
}

template <typename T, typename M>
void SimpleHeap<T,M>::restoreOrder(SimpleHeap<T,M>::Node* node)
{
    /* If there is a disorder only one method will change something */
    restoreOrderUp(node);
    restoreOrderDown(node);
}

template <typename T, typename M>
void SimpleHeap<T,M>::restoreOrderDown(SimpleHeap<T,M>::Node* node)
{
    /* If leftSon doesn't exist it means that rightSon doesn't exist either */
    if (node->leftSon == nullptr)
    {
        return;
    }
    /* If only leftSon exists it means that it is a leaf so we can end here */
    if (node->rightSon == nullptr)
    {
        if (!compare(node->value, node->leftSon->value))
        {
            swapValues(node->value, node->leftSon->value);
        }
        return;
    }
    /* Else we need to check with which son we should swap.
       We compute boolean value only once but use it twice. */
    bool leftThanRight = compare(node->leftSon->value, node->rightSon->value);
    /* We swap with firstSwaped if compare(node->value, son->value) is false 
       for both sons. If only for one we swap with that one. Else we don't
       swap and end restoring. */
    SimpleHeap<T,M>::Node* firstSwaped = leftThanRight ? node->leftSon : node->rightSon;
    SimpleHeap<T,M>::Node* secondSwaped = !leftThanRight ? node->leftSon : node->rightSon;
    if (!compare(node->value, firstSwaped->value))
    {
        swapValues(node->value, firstSwaped->value);
        restoreOrderDown(firstSwaped);
        return;
    }
    if (!compare(node->value, secondSwaped->value))
    {
        swapValues(node->value, secondSwaped->value);
        restoreOrderDown(secondSwaped);
        return;
    }
}


template <typename T, typename M>
void SimpleHeap<T,M>::restoreOrderUp(SimpleHeap<T,M>::Node* node)
{
    /* node->father == nullptr if and only if node is a root, then we can end */
    if (node->father != nullptr && !compare(node->father->value, node->value))
    {
        swapValues(node->father->value, node->value);
        restoreOrderUp(node->father);
    }
}

template <typename T, typename M>
void SimpleHeap<T,M>::insert(T v)
{
    if (size == 0)
    {
        root = new SimpleHeap<T,M>::Node(v);
        size++;
        return;
    }
    auto placeToInsert = getFirstFreePointer(v);
    restoreOrder(placeToInsert);

    size++;
}