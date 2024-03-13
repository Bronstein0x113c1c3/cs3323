#ifndef BINNODE_H
#define BINNODE_H
#include "Binnode.hpp"
#include <bits/stdc++.h>
class BST
{
private:
    Binnode *root;

public:
    BST();
    ~BST();
    BST(BST &);
    void insert(int);
    void erase(int);
    bool search(int);
    friend std::ostream &operator<<(std::ostream &, BST &);
    void inorder();
    void postorder();
    void preorder();
};
BST::BST() : root(0) {}
BST::~BST() {}
void BST::insert(int x)
{
    if (root == 0)
    {
        std::cout << "at the root..." << std::endl;
        root = new Binnode(x);
        return;
    }
    bool found = false;
    Binnode *node = root;
    while (!found)
    {
        Binnode *prev;
        if (node->value == x)
        {
            std::cout << "Found!!!" << std::endl;
            found = true;
            break;
        }
        else if (node->value > x)
        {
            std::cout << "go to the left" << std::endl;
            prev = node;
            node = node->l;
        }
        else
        {
            std::cout << "go to the right" << std::endl;
            prev = node;
            node = node->r;
        }
        if (node == 0)
        {
            std::cout << "found the location" << std::endl;

            if (x > prev->value)
            {
                std::cout << "go to the right" << std::endl;

                prev->r = new Binnode(x);
            }
            else
            {
                std::cout << "go to the left" << std::endl;

                prev->l = new Binnode(x);
            }
            found = true;
            break;
        }
    }
}
void preorder_recur(Binnode *n)
{
    while (n)
    {
        cout << " " << n->value;
        preorder_recur(n->l);
        preorder_recur(n->r);
    }
}
void BST::preorder()
{
    preorder_recur(root);
}
void inorder_recur(Binnode *n)
{
    while (n)
    {
        inorder_recur(n->l);
        cout << " " << n->value;

        inorder_recur(n->r);
    }
}
void BST::inorder()
{
    inorder_recur(root);
}

void postorder_recur(Binnode *n)
{
    while (n)
    {
        preorder_recur(n->l);
        preorder_recur(n->r);

        cout << " " << n->value;
    }
}
void BST::postorder()
{
    postorder_recur(root);
}

BST::~BST()
{
    recursively_delete(this->root);
}
void recursively_delete(Binnode *n)
{
    if (n)
    {
        recursively_delete(n->l);
        recursively_delete(n->r);
        delete n;
    }
}
void BST::erase(int x)
{
    // find the node first
    Binnode *parent = 0;
    Binnode *child = root;
    while (child != 0 && child->value != x)
    {
        parent = child;
        child = child->value > x ? child->l : child->r;
    }
    if (child == 0)
    {
        cout << "item not found" << endl;
        return;
    }
    if (child->l != 0 && child->r != 0)
    {
        parent = child;
        Binnode *node2copy = child->r;
        while (node2copy->l != 0)
        {
            parent = node2copy;
            node2copy = node2copy->l;
        }
        child->value = node2copy->value;
        child = node2copy;
    }
    if (parent == 0)
    {
        root = child->l != 0 ? child->l : child->r;
    }
    else
    {
        if (child == parent->l)
        {
            parent->l = child->l != 0 ? child->l : child->r;
        }
        else
        {
            parent->r = child->l != 0 ? child->l : child->r;
        }
    }
    delete child;
    child = 0;
}

bool BST::search(int x)
{
}
#endif