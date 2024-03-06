#include <iostream>
#include <format>
#include "LinkedList.hpp"

int main(int argc, char const *argv[])
{
    LinkedList linkedList = LinkedList();

    // To counts the nodes in a linked list
    int total_nodes = linkedList.GetTotalNodes();
    std::cout << "===============================================================" << std::endl;
    std::cout << std::format("Total Nodes: {}", total_nodes)
              << std::endl;

    // Try to Insert
    linkedList.Insert(1, 10);
    linkedList.Insert(1, 20);
    linkedList.Insert(1, 30);

    return 0;
}
