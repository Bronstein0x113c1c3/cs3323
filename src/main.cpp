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
    linkedList.InsertByIndex(1, 10);
    linkedList.InsertByIndex(3, 20);
    linkedList.InsertByIndex(4, 30);

    // Try to Print
    std::cout << "===============================================================" << std::endl;
    std::cout << linkedList << std::endl;

    // Try To Check out is empty or not
    std::cout << "===============================================================" << std::endl;
    std::cout << std::format(
        "Linked List is {}!\n",
        (linkedList.IsEmpty() ? "empty" : "not empty")
    );

    // Try to Delete a Node
    std::cout << "===============================================================" << std::endl;
    std::cout << "After Delete At Index 1!" << std::endl;
    linkedList.DeleteByIndex(3);
    std::cout << linkedList << std::endl;

                
    return 0;
}
