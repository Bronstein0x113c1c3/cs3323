#ifndef BINNODE_H
#define BINNODE_H

#include <iostream>
#include <queue>
#include <tuple>
#include <iomanip>

class BST
{
    class BinNode
    {
    public:
        int value;
        BinNode *lchild;
        BinNode *rchild;
        BinNode(int item) : value(item), lchild(nullptr), rchild(nullptr) {}
        BinNode() : lchild(nullptr), rchild(nullptr) {}
    };
    BinNode *_root;

    // Helper function for copy all nodes
    void Copy(BinNode *src_root, BinNode *dest_root);

    // Helper function for make reserve BST Tree
    void Copy_and_Reverse(BinNode *src_root, BinNode *dest_root);

    // Helper function for get total nodes
    int GetTotalNodes(BinNode *root);

    // Helper function for get total leaf nodes
    int GetLeafNodesCount(BinNode *root);

    // Helper function for get Height
    int GetHeightFromRoot(BinNode *root);

    // Helper function for recursive get level
    int GetNodeLevelFromRoot_recursiveWay(BinNode *node, bool &hasFound, int value);
    int GetNodeLevelFromRoot_nonRecursiveWay(int value);

    // Helper function for recursive tree printing
    void PrintIndentedTree(BinNode *node, int level);

    //! Kumar's Part (Don't Touch!)
    // ================================================================================
    // helper functions
    void destroybinNode(BinNode *); // help delete node
    void display(BinNode *, int);   // BinNode and indentation
    void preorderhelp(BinNode *);
    void postorderhelp(BinNode *);
    void inorderhelp(BinNode *);
    // ================================================================================
public:
    //! Kumar's Part (Don't Touch!)
    // ================================================================================
    BST();
    ~BST();
    BST(const BST &otherBST);
    void insert(int); // insert item
    void erase(int);  // erase item
    bool search(int); // search item
    void inorder();   // lchild->parent->rchild
    void postorder(); // lchild->rchild->parent
    void preorder();  // parent->lchild->rchild
    friend std::ostream &operator<<(std::ostream &, BST &);
    // ================================================================================

    /// @brief Print The Tree in a Better Format
    void PrintTree();

    /// @brief Get the Level of the Exist Value in the BST Tree
    /// @param value value in the tree
    /// @return the level in the BST Tree from the root
    int GetLevel(int value);

    /// @brief Return the Height of the BST Tree from the ROOT
    /// @return the height from the ROOT
    int GetHeight();

    /// @brief Return the Count of the Leaf Node in the BST Tree
    /// @return the Total Nodes with left == nullptr && right == nullptr
    int GetLeafCount();

    /// @brief Return the total number of nodes in the BST Tree
    /// @return the total number of nodes in the BST Tree
    int GetSize();

    /// @brief Return a new BST Tree with all the Reverse Node of the Original
    /// @return a new BST Tree with all the Reverse Node of the Original
    BST &GetMirrorImage_BST();

    /// @brief To Check Whether this is a BST or not
    /// @return true if BST else False
    bool isBST();
};

//! Kumar's Part (Don't Touch!)
// ================================================================================
BST::BST() : _root(nullptr) {}
BST::~BST()
{
    destroybinNode(_root);
}

void BST::destroybinNode(BinNode *node)
{
    if (node)
    {
        destroybinNode(node->lchild);
        destroybinNode(node->rchild);
        delete node;
    }
}

void BST::display(BinNode *node, int indent)
{
    if (node)
    {
        display(node->rchild, indent + 4);
        std::cout << std::setw(indent) << node->value << std::endl;
        display(node->lchild, indent + 4);
    }
}

void BST::preorderhelp(BinNode *node)
{
    if (node)
    {
        std::cout << " " << node->value;
        preorderhelp(node->lchild);
        preorderhelp(node->rchild);
    }
}

void BST::postorderhelp(BinNode *node)
{
    if (node)
    {
        postorderhelp(node->lchild);
        postorderhelp(node->rchild);
        std::cout << " " << node->value;
    }
}

void BST::inorderhelp(BinNode *node)
{
    if (node)
    {
        inorderhelp(node->lchild);
        std::cout << " " << node->value;
        inorderhelp(node->rchild);
    }
}

void BST::insert(int item)
{ // insert item
    if (_root == 0)
        _root = new BinNode(item); // case of the first node being added
    else
    {
        BinNode *parent = _root;
        BinNode *child = _root;
        while (child)
        { // find the place where to insert node
            parent = child;
            if (item > child->value)
                child = child->rchild;
            else if (item < child->value)
                child = child->lchild;
            else
            {
                std::cout << "Item exists \n";
                return;
            }
        }
        // once found, insert the node
        if (item > parent->value)
            parent->rchild = new BinNode(item);
        else
            parent->lchild = new BinNode(item);
    }
}

void BST::inorder()
{ // lchild->parent->rchild
    inorderhelp(_root);
    std::cout << std::endl;
}

void BST::postorder()
{ // lchild->rchild->parent
    postorderhelp(_root);
    std::cout << std::endl;
}

void BST::preorder()
{ // parent->lchild->rchild
    preorderhelp(_root);
    std::cout << std::endl;
}

void BST::erase(int item)
{ // erase item
    BinNode *parent = 0;
    BinNode *child = _root;
    // find the node with item
    while (child != 0 && child->value != item)
    {
        parent = child;
        child = child->value > item ? child->lchild : child->rchild;
    }
    if (child == 0)
    {
        std::cout << "item not found \n";
        return;
    }
    // check if the node has both the children
    if (child->lchild != 0 && child->rchild != 0)
    {
        parent = child;
        BinNode *node2copy = child->rchild;
        while (node2copy->lchild != 0)
        {
            parent = node2copy;
            node2copy = node2copy->lchild;
        }
        child->value = node2copy->value; // cpy from node2copy to child
        child = node2copy;
    }
    // now delete the child
    if (parent == 0)
        _root = child->lchild != 0 ? child->lchild : child->rchild;
    else
    {
        if (child == parent->lchild)
            parent->lchild = child->lchild != 0 ? child->lchild : child->rchild;
        else
            parent->rchild = child->lchild != 0 ? child->lchild : child->rchild;
    }
    delete child;
    child = 0;
}

bool BST::search(int item)
{ // search item
    BinNode *child = _root;
    while (child != 0 && child->value != item)
        child = child->value > item ? child->lchild : child->rchild;
    return (child == 0 ? false : true);
}

std::ostream &operator<<(std::ostream &out, BST &B)
{
    B.display(B._root, 0);
    return out;
}
// ================================================================================

void BST::PrintIndentedTree(BinNode *node, int level)
{
    if (node != nullptr)
    {
        // Print the value with appropriate indentation
        for (int i = 0; i < level; i++)
        {
            std::cout << "|-- ";
        }

        std::cout << node->value << std::endl;

        // Recursively print the left and right subtrees
        PrintIndentedTree(node->lchild, level + 1);
        PrintIndentedTree(node->rchild, level + 1);
    }
}

void BST::PrintTree()
{
    if (_root == nullptr)
    {
        std::cout << "Empty tree!" << std::endl;
        return;
    }

    // Start the recursive printing from the root
    PrintIndentedTree(_root, 0);
}

int BST::GetNodeLevelFromRoot_recursiveWay(BinNode *node, bool &hasFound, int value)
{
    int level = 0;

    // Base Case 1
    // If Not Found
    if (node == nullptr)
    {
        return 0;
    }
    // Base Case 2
    // If Found
    else if (node->value == value)
    {
        hasFound = true;
        return 0;
    }

    level = GetNodeLevelFromRoot_recursiveWay(node->lchild, hasFound, value);
    if (hasFound)
    {
        return level + 1;
    }

    level = GetNodeLevelFromRoot_recursiveWay(node->rchild, hasFound, value);
    if (hasFound)
    {
        return level + 1;
    }

    // Return Unknown Level
    return -999999;
}

int BST::GetNodeLevelFromRoot_nonRecursiveWay(int value)
{
    // Level to Return
    int current_level = 0;

    // Use BFS Approach
    BinNode *current_node = _root;
    std::queue<std::tuple<int, BinNode *>> nodes_level_to_travel;

    // Append the First node
    nodes_level_to_travel.push({current_level, current_node});

    // Traverse all the Nodes
    // Until queue is Empty!
    while (!nodes_level_to_travel.empty())
    {
        std::tuple<int, BinNode *> node_level_to_check = nodes_level_to_travel.front();
        current_level = std::get<0>(node_level_to_check);
        current_node = std::get<1>(node_level_to_check);

        nodes_level_to_travel.pop();

        // IF Null ---> Continue
        if (current_node == nullptr)
        {
            continue;
        }

        // IF Found ---> Break
        if (current_node->value == value)
        {
            return current_level;
        }

        // Not Found
        nodes_level_to_travel.push({current_level + 1, current_node->lchild});
        nodes_level_to_travel.push({current_level + 1, current_node->rchild});
    }

    // Return Unknown Level
    return -999999;
}

int BST::GetLevel(int value)
{
    // If _root is NULL
    if (_root == nullptr)
    {
        std::cout << "Empty Tree!" << std::endl;
        return -999999;
    }

    // Recursive Way
    bool hasFound = false;
    return GetNodeLevelFromRoot_recursiveWay(_root, hasFound, value); // Start by the Root of the Tree

    // Non-Recursive Way
    // return GetNodeLevelFromRoot_nonRecursiveWay(value);
}

int BST::GetHeightFromRoot(BinNode *root)
{
    // Base Case
    if (root == nullptr)
    {
        return 0;
    }

    int left_height = GetHeightFromRoot(root->lchild);
    int right_height = GetHeightFromRoot(root->rchild);

    return std::max(left_height, right_height) + 1;
}

int BST::GetHeight()
{
    // Check ROOT
    if (_root == nullptr)
    {
        std::cout << "Empty Tree!" << std::endl;
        return 0;
    }

    return GetHeightFromRoot(_root);
}

int BST::GetLeafNodesCount(BinNode *root)
{
    // Base Case 1
    if (root == nullptr)
    {
        return 0;
    }

    // Base Case 2
    // left == nullptr && right == nullptr
    bool isLeaf = (root->lchild == nullptr) && (root->rchild == nullptr);
    if (isLeaf)
    {
        return 1;
    }

    int sum = 0;
    sum += GetLeafNodesCount(root->lchild);
    sum += GetLeafNodesCount(root->rchild);

    return sum;
}

int BST::GetLeafCount()
{
    // Check Root
    if (_root == nullptr)
    {
        std::cout << "Empty Tree!" << std::endl;
        return 0;
    }

    return GetLeafNodesCount(_root);
}

int BST::GetTotalNodes(BinNode *root)
{
    // Base Case
    if (root == nullptr)
    {
        return 0;
    }

    int sum = 1;
    sum += GetTotalNodes(root->lchild);
    sum += GetTotalNodes(root->rchild);

    return sum;
}

int BST::GetSize()
{
    // Check Root
    if (_root == nullptr)
    {
        std::cout << "Empty Tree!" << std::endl;
        return 0;
    }

    return GetTotalNodes(_root);
}

void BST::Copy_and_Reverse(BinNode *src_root, BinNode *dest_root)
{
    // Base Case
    if (src_root == nullptr)
    {
        return;
    }

    // Copy src_root->left ---> dest_root->right
    BinNode *left_src_root = src_root->lchild;
    if (left_src_root != nullptr) // IF !NULL ---> Assign value
    {
        dest_root->rchild = new BinNode(left_src_root->value);
    }
    Copy_and_Reverse(left_src_root, dest_root->rchild);

    // Copy src_root->right ---> dest_root->left
    BinNode *right_src_root = src_root->rchild;
    if (right_src_root != nullptr) // IF !NULL ---> Assign value
    {
        dest_root->lchild = new BinNode(right_src_root->value);
    }
    Copy_and_Reverse(right_src_root, dest_root->lchild);
}

BST &BST::GetMirrorImage_BST()
{
    // BST Tree to return
    BST *mirrorBST = new BST();

    // Make New Root = ROOT
    BinNode *new_root = new BinNode(_root->value);
    mirrorBST->_root = new_root;

    // Traverse the Original BST Tree
    BinNode *original_root = _root;

    // Copy And Reverse
    Copy_and_Reverse(original_root, new_root);

    return *mirrorBST;
}

bool BST::isBST()
{
    // Use BFS Approach
    BinNode *current_node_left = nullptr;
    BinNode *current_node_right = nullptr;
    BinNode *current_node = _root;
    std::queue<BinNode *> nodes_to_travel;

    // Append the First node
    nodes_to_travel.push(current_node);

    // Traverse all the Nodes
    // Until queue is Empty!
    while (!nodes_to_travel.empty())
    {
        current_node = nodes_to_travel.front();
        nodes_to_travel.pop();

        // IF Null ---> Continue
        if (current_node == nullptr)
        {
            continue;
        }

        // Check Left
        bool isLeftValid = true;
        current_node_left = current_node->lchild;
        if (current_node_left != nullptr)
        {
            isLeftValid = current_node->value >= current_node_left->value;
        }
        
        // Check Right
        bool isRightValid = true;
        current_node_right = current_node->rchild;
        if (current_node_right != nullptr)
        {
            isRightValid = current_node->value <= current_node_right->value;
        }

        // Check if isValidLeft and isValidRight == false ---> Return Immediately
        if (!(isLeftValid && isRightValid))
        {
            return false;
        }

        // Push next nodes
        nodes_to_travel.push(current_node_left);
        nodes_to_travel.push(current_node_right);
    }

    // When all Case has Evaluated ---> True
    return true;
}

void BST::Copy(BinNode *src_root, BinNode *dest_root)
{
    // Base Case
    if (src_root == nullptr)
    {
        return;
    }

    // src_root->left ---> dest_root->left
    BinNode *src_root_left = src_root->lchild;
    if (src_root_left != nullptr)
    {
        dest_root->lchild = new BinNode(src_root_left->value);
    }
    Copy(src_root_left, dest_root->lchild);

    // src_root->right ---> dest_root->right
    BinNode *src_root_right = src_root->rchild;
    if (src_root_right != nullptr)
    {
        dest_root->rchild = new BinNode(src_root_right->value);
    }
    Copy(src_root_right, dest_root->rchild);
}

BST::BST(const BST &otherBST)
{
    // Make Root
    BinNode *src_root = otherBST._root;
    this->_root = new BinNode(src_root->value);

    // Copy Original ---> Dest
    Copy(src_root, this->_root);
}

#endif