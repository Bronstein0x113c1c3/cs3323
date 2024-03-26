#ifndef NOPE_HPP
#define NODE_HPP

template <typename Key, typename Value>
struct Node
{
    Key _key;
    Value _value;
    Node* _next = nullptr;

    Node(const Key &key, const Value &value) : _key(key), _value(value){};
    Node(const Key &key, Value &&value) : _key(key), _value(value){};
    ~Node() {}
};

#endif