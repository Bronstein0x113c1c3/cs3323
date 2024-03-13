#ifndef BINNODE_HPP
#define BINNODE_HPP

class Binnode
{
public:
    int value;
    Binnode *l, *r;
    Binnode() : l(0), r(0){};
    Binnode(int value) : value(value), l(0), r(0){};
    ~Binnode(){}
};

#endif