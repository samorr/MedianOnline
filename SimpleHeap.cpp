#include "SimpleHeap.h"

template <typename T>
auto SimpleHeap<T>::getNodeAfterAddOrRemove
    (std::size_t way, bool remove, bool add, T v)
{
    if (remove && add)
    {
        throw std::invalid_argument("Can't add and remove at the same time!");
    }
    auto nodePointer = root;
    /* This situation shouldn't happen with normal usage of this method. */
    if (way == 1)
    {
        throw std::logic_error
            ("Attempting to get access to root in illegal way! Use removeRoot or getRootValue method.");
    }
    /* We can find way to first free pointer with reversed binary notation
       of heap size. */
    std::size_t binaryMask = 1;
    /* binaryMask has to be as long as way and contains only 1's. */
    while(binaryMask < way)
    {
        binaryMask <<= 1;
        binaryMask++;
    }
    /* First we want to forget most significant bit, because it encodes root. */
    binaryMask >>= 1;
    way &= binaryMask;
    while(true)
    {
        binaryMask >>= 1;
        /* Sons are leafs if binaryMask has ended. */
        if (binaryMask == 0)
        {
            /* Now we have to distinguish between adding and removing. */
            if (way == 0)
            {
                auto returnNode = nodePointer->leftSon;
                if (remove)
                {
                    returnNode->father = nullptr;
                    nodePointer->leftSon = nullptr;
                }
                else if (add) 
                {
                    returnNode = new SimpleHeap<T>::Node(v);
                    nodePointer->leftSon = returnNode;
                    returnNode->father = nodePointer;
                }
                return returnNode;
            }
            auto returnNode = nodePointer->rightSon;
            if (remove)
            {
                returnNode->father = nullptr;
                nodePointer->rightSon = nullptr;
            }
            else if (add)
            {
                returnNode = new SimpleHeap<T>::Node(v);
                nodePointer->rightSon = returnNode;
                returnNode->father = nodePointer;
            }
            return returnNode;
        }
        /* Checking if most significant bit in way is 0 or 1. If 0 we should take
           left son, else right son. */
        nodePointer = (way & ~binaryMask) == 0 ?
                                nodePointer->leftSon :
                                nodePointer->rightSon;
        /* Forgetting most significant bit of way. */
        way &= binaryMask;
    }
}

template <typename T>
T SimpleHeap<T>::removeRoot()
{
    /* When heap contains only root we treat it in different way. */
    T value = root->value;
    if (size == 1)
    {
        size--;
        delete root;
        root = nullptr;
        return value;
    }
    /* T is numeric type so we can cast 0 to it. This parameter doesn't matter
       anyway. */
    auto lastNode = getNodeAfterAddOrRemove(size, true, false, static_cast<T>(0));
    lastNode->leftSon = root->leftSon;
    lastNode->rightSon = root->rightSon;
    /* rightSon can exist only if leftSon exists */
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

template <typename T>
void SimpleHeap<T>::restoreOrderDown(SimpleHeap<T>::Node* node)
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
    auto firstSwaped = leftThanRight ? node->leftSon : node->rightSon;
    auto secondSwaped = !leftThanRight ? node->leftSon : node->rightSon;
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


template <typename T>
void SimpleHeap<T>::restoreOrderUp(SimpleHeap<T>::Node* node)
{
    /* father == nullptr if and only if node is a root, then we can end */
    if (node->father != nullptr && !compare(node->father->value, node->value))
    {
        swapValues(node->father->value, node->value);
        /* When we add leaf we need to restore order in up direction. */
        restoreOrderUp(node->father);
    }
}

template <typename T>
void SimpleHeap<T>::insert(T v)
{
    /* To empty heap we add root and that's all. */
    if (size == 0)
    {
        root = new SimpleHeap<T>::Node(v);
        size++;
        return;
    }
    /* Else we need to add new node in right place. */
    auto placeOfInsert = getNodeAfterAddOrRemove(size+1, false, true, v);
    restoreOrderUp(placeOfInsert);
    size++;
}