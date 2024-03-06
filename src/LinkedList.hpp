#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"

class LinkedList
{
private:
    Node* _head;
public:
    LinkedList();
    ~LinkedList();

    int GetTotalNodes();
};

LinkedList::LinkedList() : _head(nullptr) {}

LinkedList::~LinkedList() 
{
    Node* current_node = this->_head;
    
    while (current_node != nullptr)
    {
        Node* node_to_delete = current_node;

        // Move to the next Node
        current_node = current_node->_next;
        delete node_to_delete;
    }

    // Assign the nullptr for the HEAD
    // To prevent memory leak
    _head = nullptr;
}

int LinkedList::GetTotalNodes()
{
    // Counter to return
    int counter = 0;

    Node* current_node = this->_head;
    while (current_node != nullptr)
    {
        counter++;

        // Move to the next node -> To increase the counter
        current_node = current_node->_next;
    }
    
    return counter;
}

#endif