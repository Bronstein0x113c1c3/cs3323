#include "Stack.hpp"
#include <iostream>
#include <format>

int main(int argc, char const *argv[])
{
    Stack numStack = Stack();

    // Try to Push the Value
    std::cout << "===============================================================" << std::endl;
    numStack.Push(10);
    numStack.Push(20);
    numStack.Push(30);

    // Try To Get the Top Value
    std::cout << "===============================================================" << std::endl;
    int topValue = numStack.Top();
    std::cout << std::format(
        "Top Value: {}\n",
        topValue);

    // Try to Pop The Value and Get the Top After that
    std::cout << "===============================================================" << std::endl;
    numStack.Pop();
    topValue = numStack.Top();
    std::cout << std::format(
        "Top Value after Pop: {}\n",
        topValue);

    // Pop Until there is No Element Left to pop
    std::cout << "===============================================================" << std::endl;
    numStack.Pop();
    numStack.Pop();
    numStack.Pop();

    // Check if the Stack is Empty
    std::cout << "===============================================================" << std::endl;
    bool isEmpty = numStack.Empty();
    std::cout << std::format(
        "The Stack {} Empty!\n",
        isEmpty ? "is" : "is not" 
    );

    return 0;
}
