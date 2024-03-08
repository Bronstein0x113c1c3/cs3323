#include "Queue.hpp"
#include "Stack.hpp"
#include <iostream>
#include <format>

int main(int argc, char const *argv[])
{
    // Stack section
    // ===============================================================
    std::cout << "===============================================================" << std::endl;
    std::cout << "Stack Section!" << std::endl;
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
    bool isStackEmpty = numStack.Empty();
    std::cout << std::format(
        "The Stack {} Empty!\n",
        isStackEmpty ? "is" : "is not" 
    );

    // Queue Section
    // ===============================================================
    std::cout << "===============================================================" << std::endl;
    std::cout << "Queue Section!" << std::endl;
    Queue numQueue = Queue();

    // Try to Push the Value
    std::cout << "===============================================================" << std::endl;
    numQueue.Enqueue(10);
    numQueue.Enqueue(20);
    numQueue.Enqueue(30);

    // Try To Get the Top Value
    std::cout << "===============================================================" << std::endl;
    int headValue = numQueue.Front();
    std::cout << std::format(
        "HEAD Value: {}\n",
        headValue);

    // Try to Pop The Value and Get the Top After that
    std::cout << "===============================================================" << std::endl;
    numQueue.Dequeue();
    headValue = numQueue.Front();
    std::cout << std::format(
        "HEAD Value after Dequeue: {}\n",
        headValue);

    // Pop Until there is No Element Left to pop
    std::cout << "===============================================================" << std::endl;
    numQueue.Dequeue();
    numQueue.Dequeue();
    numQueue.Dequeue();

    // Check if the Queue is Empty
    std::cout << "===============================================================" << std::endl;
    bool isQueueEmpty = numQueue.Empty();
    std::cout << std::format(
        "The Queue {} Empty!\n",
        isQueueEmpty ? "is" : "is not" 
    );

    return 0;
}
