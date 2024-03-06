#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"
#include <iostream>

class LinkedList
{
private:
    Node *_head;

public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList &other);

    int GetTotalNodes();
    bool IsEmpty();
    void InsertByIndex(int indexToInsert, int value);
    void DeleteByIndex(int indexToDelete);

    friend std::ostream &operator<<(std::ostream &os, const LinkedList &linkedList);
};

LinkedList::LinkedList() : _head(nullptr) {}

LinkedList::~LinkedList()
{
    Node *current_node = this->_head;

    while (current_node != nullptr)
    {
        Node *node_to_delete = current_node;

        // Move to the next Node
        current_node = current_node->_next;
        delete node_to_delete;
    }

    // Assign the nullptr for the HEAD
    // To prevent memory leak
    _head = nullptr;
}

LinkedList::LinkedList(const LinkedList &other)
{
    // Assign the Head
    this->_head = new Node(other._head->_value);

    // Make 2 pointer to keep track Other and This
    Node *this_current_node = this->_head;
    Node *other_current_node = other._head->_next;

    while (other_current_node != nullptr)
    {
        // Make a node
        this_current_node->_next = new Node(other_current_node->_value);

        // Move to the next node
        other_current_node = other_current_node->_next;
    }
}

std::ostream &operator<<(std::ostream &os, const LinkedList &linkedList)
{
    os << "===============================================================" << std::endl;
    os << "Linked List:" << std::endl;
    os << "HEAD: ";

    // Current Node to track
    Node *current_node = linkedList._head;
    while (current_node != nullptr)
    {
        os << current_node->_value << " ---> ";

        // Move to the next node
        current_node = current_node->_next;
    }
    os << "NULL";

    return os;
}

int LinkedList::GetTotalNodes()
{
    // Counter to return
    int counter = 0;

    Node *current_node = this->_head;
    while (current_node != nullptr)
    {
        counter++;

        // Move to the next node -> To increase the counter
        current_node = current_node->_next;
    }

    return counter;
}

bool LinkedList::IsEmpty()
{
    // IF Empty -> Head == null
    return this->_head == nullptr;
}

/// @brief Insert at indexToInsert with the value. LinkedList start with index 0
/// @param indexToInsert must larger than 0
/// @param value
void LinkedList::InsertByIndex(int indexToInsert, int value)
{
    if (indexToInsert < 0)
    {
        std::cout << "===============================================================" << std::endl;
        std::cerr << "Illegal Position!" << std::endl;
        std::cerr << "Index Must Start From 0" << std::endl;
        return;
    }

    // Node to insert
    Node *newNode = new Node(value);

    // Insert At Head
    if (indexToInsert == 0 || this->_head == nullptr)
    {
        std::cout << "===============================================================" << std::endl;
        std::cout << "Insert!" << std::endl;

        newNode->_next = this->_head;
        this->_head = newNode;
        return;
    }

    // Node to travel
    Node *prev_node = nullptr;
    Node *current_node = this->_head;

    for (size_t index = 0; index < indexToInsert; index++)
    {
        // If Found
        if (current_node == nullptr)
        {
            break;
        }

        prev_node = current_node;
        current_node = current_node->_next;
    }

    // Assign the Node
    std::cout << "===============================================================" << std::endl;
    std::cout << "Insert!" << std::endl;

    prev_node->_next = newNode;
    newNode->_next = current_node;
}

/// @brief Delete A Node in the LinkedList by index. LinkedList start with index 0
/// @param indexToDelete must larger than 0
void LinkedList::DeleteByIndex(int indexToDelete)
{
    // If this LinkedList has no HEAD
    if (this->_head == nullptr)
    {
        std::cout << "===============================================================" << std::endl;
        std::cerr << "Linked List has no Node to Delete!";
        return;
    }

    // If Index is Negative
    if (indexToDelete < 0)
    {
        std::cout << "===============================================================" << std::endl;
        std::cerr << "Illegal Position!" << std::endl;
        std::cerr << "Index Must Start From 0" << std::endl;
        return;
    }

    // If Index is the HEAD of the LinkedList
    if (indexToDelete == 0)
    {
        // Change the new HEAD
        Node *node_to_delete = this->_head;
        this->_head = node_to_delete->_next;

        delete node_to_delete;
        return;
    }

    // If the node to delete is in the middle
    // 2 Node to travel
    Node *prev_node = nullptr;
    Node *node_to_delete = this->_head;

    bool canDelete = true;
    for (size_t index = 0; index < indexToDelete; index++)
    {
        prev_node = node_to_delete;
        node_to_delete = node_to_delete->_next;

        // If Out or Bound of the LinkedList
        if (node_to_delete == nullptr)
        {
            canDelete = false;
            break;
        }
    }

    // Delete the Node to delete
    if (canDelete)
    {
        prev_node->_next = node_to_delete->_next;
        delete node_to_delete;
        return;
    }

    // Out of Bound -> Cannot Delete
    std::cout << "===============================================================" << std::endl;
    std::cerr << "Index Out Of Bounds!" << std::endl;
    std::cerr << "Cannot Delete!" << std::endl;
}

#endif