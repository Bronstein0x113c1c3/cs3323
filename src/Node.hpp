#ifndef NODE_HPP
#define NODE_HPP

struct Node
{
    int _value;
    Node *_next;

    Node() : _value(0), _next(nullptr){};
    Node(int value) : _value(value), _next(nullptr){};
    Node(int value, Node *next) : _value(value), _next(next){};
    
    ~Node() {};
};

#endif