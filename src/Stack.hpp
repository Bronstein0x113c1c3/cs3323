#include <queue>
#include <iostream>
#include <format>

class Stack
{
private:
    std::queue<int> _tempQueue;
    std::queue<int> _permanentQueue;

public:
    Stack(){};
    ~Stack(){};

    /// @brief Return the top element
    /// @return the reference of the top element in the Stack
    int &Top();

    /// @brief To check if the Stack is Empty
    /// @return is empty of not ?
    bool Empty();

    /// @brief Push value into the Stack
    void Push(const int &value);

    /// @brief Pop the Top Element in the Stack
    void Pop();
};

int &Stack::Top()
{
    return _permanentQueue.front();
}

bool Stack::Empty()
{
    return _permanentQueue.empty();
}

void Stack::Push(const int &value)
{
    // Push the Value into the _tempQueue
    // If _permanentQueue is not Empty
    // ---> Push all value into _tempQueue
    // Swap content the 2 Queues

    // Push the Value into the _tempQueue
    _tempQueue.push(value);

    // Check if _permanentQueue is Empty
    while (!_permanentQueue.empty())
    {
        // Push all the value into _tempQueue
        int value = _permanentQueue.front();
        _tempQueue.push(std::move(value));

        // Pop the value
        _permanentQueue.pop();
    }

    // Swap the 2 Queues
    std::swap(_tempQueue, _permanentQueue);

    // Print out a Log
    std::cout << std::format(
        "Push {} in the Stack\n",
        value);
}

void Stack::Pop()
{
    // Check if Queue has Element Left
    if (_permanentQueue.empty())
    {
        std::cerr << "No Element Left to Pop!" << std::endl;
        return;
    }

    std::cout << std::format(
        "Pop the {} out of the Stack\n",
        _permanentQueue.front());

    // Pop the value from the _permanentQueue
    // (Where actual value hold)
    _permanentQueue.pop();
}