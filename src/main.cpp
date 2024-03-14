#include "BST.hpp"
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <format>

int main()
{
    srand(time(0));
    BST tree;
    for (int i = 0; i < 10; i++)
    {
        int insert_value = rand() % 51;

        tree.insert(insert_value);
        std::cout << std::format("Insert {} into BST Tree!\n", insert_value);
    }
    std::cout << "inorder:\n ";
    tree.inorder();
    std::cout << "preorder:\n ";
    tree.preorder();
    std::cout << "postorder:\n ";
    tree.postorder();
    // int item;

    // for (int i = 0; i < 5; i++)
    // {
    //     std::cout << "enter item to delete \n";
    //     std::cin >> item;
    //     tree.erase(item);
    //     std::cout << tree << "\n \n \n";
    //     std::cout << " to erase next number: \n";
    //     system("pause");
    // }
    // system("pause");

    // Try to Print Tree A Better Format
    // ===============================================================
    std::cout << "===============================================================" << std::endl;
    tree.PrintTree();

    // Try to Get Level of Some Value in the BST Tree (Recursive Way && Non Recursive Way)
    // ===============================================================
    std::cout << "===============================================================" << std::endl;
    int value;
    std::cout << "Enter the Value to check Level: ";
    std::cin >> value;
    int level = tree.GetLevel(value);
    std::cout << std::format("{} is in {} from ROOT!\n", value, level);

    // Try to Get Heigh of BST Tree
    // ===============================================================
    std::cout << "===============================================================" << std::endl;
    int treeHeight = tree.GetHeight();
    std::cout << std::format("Tree Height: {}\n", treeHeight);

    // Try to Get Total Leaf Node in the BST Tree
    // ===============================================================
    std::cout << "===============================================================" << std::endl;
    int totalLeafNodes = tree.GetLeafCount();
    std::cout << std::format("Total Leaf: {}\n", totalLeafNodes);

    // Try to Get Total Nodes in the BST Tree
    // ===============================================================
    std::cout << "===============================================================" << std::endl;
    int totalNodes = tree.GetSize();
    std::cout << std::format("Total Nodes: {}\n", totalNodes);

    return 0;
}
