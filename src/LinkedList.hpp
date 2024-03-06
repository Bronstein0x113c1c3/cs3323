#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include "Node.hpp"
#include <iostream>

class LinkedList
{
private:
    Node *_head;

    // Helper Function to Recursively Reverse
    Node *ReverseAllNodesRecursively(Node *current_node = nullptr);

public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList &other);

    // Mics Functions
    int GetTotalNodes();
    bool IsEmpty();
    void TraverseAllNodes();

    // Search Functions
    Node *SearchLinear(const int valueToSearch);

    // Insert Functions
    void InsertByIndex(int indexToInsert, int value);

    // Delete Functions
    void DeleteByIndex(int indexToDelete);
    void DeleteAll();

    // Reverse Function
    void ReverseAllNodes();

    LinkedList &operator=(const LinkedList &other);
    friend std::ostream &operator<<(std::ostream &os, const LinkedList &linkedList);
};

LinkedList::LinkedList() : _head(nullptr) {}

LinkedList::~LinkedList()
{
    this->DeleteAll();
}

LinkedList::LinkedList(const LinkedList &other)
{
    // Check if other has HEAD
    if (other._head == nullptr)
    {
        return;
    }

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
        this_current_node = this_current_node->_next;
    }
}

LinkedList &LinkedList::operator=(const LinkedList &other)
{
    // Avoid self-assignment
    if (this == &other)
    {
        return *this;
    }

    // Delete all existing resource
    this->DeleteAll();

    // Deep Copy all the Node From other --> this
    // ========================================================================
    // Check if other has HEAD
    if (other._head == nullptr)
    {
        return *this;
    }

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
        this_current_node = this_current_node->_next;
    }

    return *this;
}

std::ostream &operator<<(std::ostream &os, const LinkedList &linkedList)
{
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

void LinkedList::TraverseAllNodes()
{
    std::cout << *this << std::endl;
}

Node *LinkedList::SearchLinear(const int valueToSearch)
{
    // Node to return
    Node *result_node = this->_head;

    // Linear Search the Linked List
    while (result_node != nullptr)
    {
        if (result_node->_value == valueToSearch)
        {
            break;
        }

        // Move to the next node
        result_node = result_node->_next;
    }

    return result_node;
}

/// @brief Insert at indexToInsert with the value. LinkedList start with index 0
/// @param indexToInsert must larger than 0
/// @param value
void LinkedList::InsertByIndex(int indexToInsert, int value)
{
    if (indexToInsert < 0)
    {
        std::cerr << "Illegal Position!" << std::endl;
        std::cerr << "Index Must Start From 0" << std::endl;
        return;
    }

    // Node to insert
    Node *newNode = new Node(value);

    // Insert At Head
    if (indexToInsert == 0 || this->_head == nullptr)
    {
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

        std::cerr << "Linked List has no Node to Delete!";
        return;
    }

    // If Index is Negative
    if (indexToDelete < 0)
    {

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
    std::cerr << "Index Out Of Bounds!" << std::endl;
    std::cerr << "Cannot Delete!" << std::endl;
}

void LinkedList::DeleteAll()
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

void LinkedList::ReverseAllNodes()
{
    // Don't Has HEAD ---> Can Not Reverse
    if (this->_head == nullptr)
    {
        return;
    }

    this->ReverseAllNodesRecursively();
}

/// @brief Reverse the LinkedList using Stack FIFO principle
/// @param current_node The Current Node
/// @return The Next Node
Node *LinkedList::ReverseAllNodesRecursively(Node *current_node)
{
    // Base Case
    // Reach the Last Node
    if (current_node != nullptr)
    {
        if (current_node->_next == nullptr)
        {
            // Assign the new HEAD
            this->_head = current_node;
            return current_node;
        }
    }

    Node *next_node = nullptr;
    if (current_node == nullptr)
    {
        next_node = ReverseAllNodesRecursively(this->_head);
    }
    else
    {
        next_node = ReverseAllNodesRecursively(current_node->_next);
    }
    next_node->_next = current_node;
    return current_node;
}

#endif