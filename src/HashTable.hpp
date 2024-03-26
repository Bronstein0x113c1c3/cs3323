#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include "Node.hpp"
#include <vector>
#include <functional>
#include <iostream>
#include <format>

template <typename Key, typename Value>
class HashTable
{
private:
    std::size_t MAX_SIZE;
    std::vector<Node<Key, Value> *> _table;

    std::size_t Compress(std::size_t hash_value)
    {
        return hash_value % MAX_SIZE;
    };

public:
    HashTable(std::size_t max_size);
    HashTable(const HashTable &other);
    ~HashTable();

    void Insert(const Key &key, const Value &value);
    void Insert(const Key &key, Value &&value);

    Value* Search(const Key &key);

    void Delete(const Key &key);

    void Print() const;
};

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(std::size_t max_size)
{
    // Init the Vector with a length of fixed Length
    MAX_SIZE = max_size;
    _table = std::vector<Node<Key, Value> *>(MAX_SIZE);
}

template <typename Key, typename Value>
HashTable<Key, Value>::HashTable(const HashTable &other)
{
    // Make a Table to store key, value
    this->MAX_SIZE = other.MAX_SIZE;
    this->_table = std::vector<Node<Key, Value> *>(this->MAX_SIZE);

    // Copy every node from other into this
    for (size_t index = 0; index < this->MAX_SIZE; index++)
    {
        Node<Key, Value> *current_node = other._table.at(index);
        if (current_node == nullptr)
        {
            continue;
        }

        // Assign node to this at index
        Node<Key, Value> *node_to_insert = new Node<Key, Value>(current_node->_key, current_node->_value);
        this->_table.at(index) = node_to_insert;

        // If After the current_node, There is a Node
        while (current_node->_next != nullptr)
        {
            // Move to the next node
            current_node = current_node->_next;

            node_to_insert->_next = new Node<Key, Value>(current_node->_key, current_node->_value);
            node_to_insert = node_to_insert->_next;
        }
    }
}

template <typename Key, typename Value>
HashTable<Key, Value>::~HashTable()
{
    for (Node<Key, Value> *node : _table)
    {
        // Deallocate Every Node in the current_node
        Node<Key, Value> *current_node = node;
        Node<Key, Value> *node_to_delete = current_node;
        while (node_to_delete != nullptr)
        {
            current_node = current_node->_next;
            delete node_to_delete;
            node_to_delete = current_node;
        }
    }
}

template <typename Key, typename Value>
void HashTable<Key, Value>::Insert(const Key &key, const Value &value)
{
    // Hash the Key
    std::size_t key_hash = std::hash<Key>{}(key);

    // Compress the Value
    int table_index = Compress(key_hash);

    // Put into the Table according to that index
    Node<Key, Value> *prev_node = nullptr;
    Node<Key, Value> *current_node = _table.at(table_index);
    while (current_node != nullptr)
    {
        // If found a duplicate key
        if (key == current_node->_key)
        {
            std::cerr << "Cannot Insert Duplicate Key!" << std::endl;
            return;
        }

        // Loop until find a spot to insert
        prev_node = current_node;
        current_node = current_node->_next;
    }

    // Then Insert at that position
    Node<Key, Value> *node_to_insert = new Node<Key, Value>(key, value);
    if (prev_node == nullptr)
    {
        _table.at(table_index) = node_to_insert;
        return;
    }

    prev_node->_next = node_to_insert;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::Insert(const Key &key, Value &&value)
{
    // Hash the Key
    std::size_t key_hash = std::hash<Key>{}(key);

    // Compress the Value
    int table_index = Compress(key_hash);

    // Put into the Table according to that index
    Node<Key, Value> *prev_node = nullptr;
    Node<Key, Value> *current_node = _table.at(table_index);
    while (current_node != nullptr)
    {
        // If found a duplicate key
        if (key == current_node->_key)
        {
            std::cerr << "Cannot Insert Duplicate Key!" << std::endl;
            return;
        }

        // Loop until find a spot to insert
        prev_node = current_node;
        current_node = current_node->_next;
    }

    // Then Insert at that position
    Node<Key, Value> *node_to_insert = new Node<Key, Value>(key, value);
    if (prev_node == nullptr)
    {
        _table.at(table_index) = node_to_insert;
        return;
    }

    prev_node->_next = node_to_insert;
};

template <typename Key, typename Value>
Value* HashTable<Key, Value>::Search(const Key &key)
{
    // Node to Search
    Node<Key, Value> *node_to_search = nullptr;

    // Hash the Key
    std::size_t key_hash = std::hash<Key>{}(key);

    // Compress the Value
    int table_index = Compress(key_hash);

    // Look for that node
    Node<Key, Value> *current_node = _table.at(table_index);
    while (current_node != nullptr)
    {
        // Check key
        if (key == current_node->_key)
        {
            node_to_search = current_node;
            break;
        }

        current_node = current_node->_next;
    }

    // Throw an error
    if (node_to_search == nullptr)
    {
        throw std::out_of_range("Invalid Key!");
    }

    return &node_to_search->_value;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::Delete(const Key &key)
{
    // Hash the Key
    std::size_t key_hash = std::hash<Key>{}(key);

    // Compress the Value
    int table_index = Compress(key_hash);

    // Put into the Table according to that index
    Node<Key, Value> *prev_node = nullptr;
    Node<Key, Value> *current_node = _table.at(table_index);
    while (current_node != nullptr)
    {
        // If found the key to delete
        if (key == current_node->_key)
        {
            break;
        }

        // Loop until find a spot to insert
        prev_node = current_node;
        current_node = current_node->_next;
    }

    // If not found
    if (current_node == nullptr)
    {
        return;
    }

    // Delete that key
    Node<Key, Value> *node_to_delete = current_node;
    bool isRoot = (prev_node == nullptr);
    if (isRoot) // Check the node_to_delete is Root
    {
        // If there is element behind
        if (current_node->_next != nullptr)
        {
            _table.at(table_index) = current_node->_next;
            goto deleteNode;
        }

        // If there is no element behind
        // Assign the Prev --> current.next
        _table.at(table_index) = nullptr;
        goto deleteNode;
    }

    // If not Root
    // Assign the Prev --> current.next
    prev_node->_next = current_node->_next;

// Delete the node
deleteNode:
    delete node_to_delete;
}

template <typename Key, typename Value>
void HashTable<Key, Value>::Print() const
{
    std::cout << "Hash Table!" << std::endl;
    for (size_t index = 0; index < MAX_SIZE; index++)
    {
        std::cout << std::format(
            "[{}]: ",
            index

        );

        // Print the key
        Node<Key, Value> *current_node = _table.at(index);
        while (current_node != nullptr)
        {
            std::cout << std::format(
                "{} ---> ",
                current_node->_key

            );

            current_node = current_node->_next;
        }

        std::cout << "NULL" << std::endl;
    }
}

#endif