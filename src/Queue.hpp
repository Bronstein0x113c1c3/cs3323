#include <stack>
#include <iostream>
#include <format>

class Queue
{
private:
    std::stack<int> _tempStack;
    std::stack<int> _permanentStack;
public:
    Queue() {};
    ~Queue() {};

    /// @brief To get the reference of the HEAD of the Queue
    /// @return Reference of the HEAD of the Queue
    int& Front();

    /// @brief To Check if the Queue is Empty or not ?
    /// @return Is Queue Empty ?
    bool Empty();

    /// @brief To Enqueue the value into the HEAD of the Queue
    /// @param value Value need to Enqueue
    void Enqueue(const int& value);

    /// @brief To Dequeue the HEAD value out of the Queue
    void Dequeue();
};

int& Queue::Front()
{
    // Return the Reference from the Top of _permanentStack
    return _permanentStack.top();
}

bool Queue::Empty()
{
    // Check if _permanentStack is empty
    return _permanentStack.empty();
}

void Queue::Enqueue(const int& value)
{
    // ======================================================================
    // Push Every Element from the _permanentStack ---> _tempStack
    // Push the value into the _tempStack
    
    // Finally
    // ---> Push Every Element from the _tempStack ---> _permanentStack
    // ======================================================================

    // Push Every Element from the _permanentStack ---> _tempStack
    int permanentStack_value;
    while (!_permanentStack.empty())
    {
        // Get the Stack Value
        permanentStack_value = _permanentStack.top();

        // Push into the _tempStack
        _tempStack.push(std::move(permanentStack_value));

        // Move to the next Element in the Stack
        _permanentStack.pop();
    }

    // Push the value into the _tempStack
    _tempStack.push(value);
    
    // Finally
    // ---> Push Every Element from the _tempStack ---> _permanentStack
    int tempStack_value;
    while (!_tempStack.empty())
    {
        // Get the Stack Value
        tempStack_value = _tempStack.top();

        // Push into the _tempStack
        _permanentStack.push(std::move(tempStack_value));

        // Move to the next Element in the Stack
        _tempStack.pop();
    }

    // Print out a Log
    std::cout << std::format(
        "Enqueue {} into the Queue!\n",
        value
    );
}

void Queue::Dequeue()
{
    // If empty
    // ---> Cannot Dequeue
    if (_permanentStack.empty())
    {
        std::cerr << "No Element left to Dequeue!" << std::endl;
        return;
    }

    // Print Out a Log
    std::cout << std::format(
        "Dequeue {} out of the Queue!\n",
        _permanentStack.top()
    );
    

    // Pop the Value from the _permanentStack
    _permanentStack.pop();
}