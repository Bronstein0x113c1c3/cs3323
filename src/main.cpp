#include <iostream>
#include <format>
#include "LinkedList.hpp"

int main(int argc, char const *argv[])
{
    LinkedList linkedList1 = LinkedList();

    // To counts the nodes in a linked list
    int total_nodes = linkedList1.GetTotalNodes();
    std::cout << "===============================================================" << std::endl;
    std::cout << std::format("Total Nodes: {}", total_nodes)
              << std::endl;

    // Try to Insert
    linkedList1.InsertByIndex(1, 10);
    linkedList1.InsertByIndex(3, 20);
    linkedList1.InsertByIndex(4, 30);

    // Try to Print
    std::cout << "===============================================================" << std::endl;
    std::cout << linkedList1 << std::endl;

    // Try To Check out is empty or not
    std::cout << "===============================================================" << std::endl;
    std::cout << std::format(
        "Linked List is {}!\n",
        (linkedList1.IsEmpty() ? "empty" : "not empty"));

    // Try to Delete a Node
    std::cout << "===============================================================" << std::endl;
    int indexToDelete = 3;
    std::cout << std::format("After Delete At Index {}!", indexToDelete) << std::endl;
    linkedList1.DeleteByIndex(indexToDelete);
    std::cout << linkedList1 << std::endl;

    // Try To Assign A New LinkedList
    std::cout << "===============================================================" << std::endl;
    LinkedList linkedList2 = LinkedList();
    // linkedList2.InsertByIndex(0, 10000);
    // linkedList2.InsertByIndex(1, 20000);
    // linkedList2.InsertByIndex(2, 30000);

    std::cout << "Before Assigned: " << std::endl;

    std::cout << linkedList1
              << std::endl
              << std::endl;

    linkedList1 = linkedList2;
    std::cout << "After Assigned: " << std::endl;

    std::cout << linkedList1
              << std::endl
              << std::endl;

    // Try to Traverse the LinkedList
    // linkedList1.TraverseAllNodes();

    // Try to Search the LinkedList
    std::cout << "===============================================================" << std::endl;
    int valueToSearch = 30000;
    Node *nodeToSearch = linkedList1.SearchLinear(valueToSearch);

    bool isExist = nodeToSearch != nullptr;
    if (!isExist)
    {
        std::cout << std::format("Value {} is not exist in the LinkedList!", valueToSearch)
                  << std::endl;
    }
    else
    {
        std::cout << "Value " << valueToSearch << " is exist at memory " << nodeToSearch << " in the LinkedList!"
                  << std::endl;
    }

    // Try to Reverse the LinkedList
    std::cout << "===============================================================" << std::endl;
    std::cout << "Before Reverse: " << std::endl;
    std::cout << linkedList1
              << std::endl
              << std::endl;

    linkedList1.ReverseAllNodes();
    std::cout << "After Reverse: " << std::endl;
    std::cout << linkedList1
              << std::endl
              << std::endl;

    return 0;
}
