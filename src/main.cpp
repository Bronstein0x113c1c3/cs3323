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

    return 0;
}
