#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <unordered_map>
#include <functional>

const std::unordered_map<char, int> Operator_Priority_Map = {
    {'^', 3},
    {'*', 2},
    {'/', 2},
    {'+', 1},
    {'-', 1}};

bool isOperatorInStack_hasHigherPriority(const std::stack<char> &operatorsStack, char currentOperator);

//! Some Limit: Cannot work with nested Parenthesis (Ex: ((1 + 2) – 3 * (4 / 5)) + 6 )
std::string infixToPostfixNotation(const std::string &infixNotation);

int main(int argc, char const *argv[])
{
    std::cout << "===============================================================" << std::endl;
    std::string infixNotation = "8 * (5 ^ 4 + 2) - 6 ^ 2 / (9 * 3)";
    std::string postfixNotation = infixToPostfixNotation(infixNotation);

    std::cout << "Infix Notation: "
              << infixNotation
              << std::endl;

    std::cout << "Postfix Notation: "
              << postfixNotation
              << std::endl;

    return 0;
}

/// @brief Take an Infix Notation transfer to Postfix Notation
/// @param infixNotation Infix Notation Input
/// @return Postfix Notation
std::string infixToPostfixNotation(const std::string &infixNotation)
{
    // Postfix Notation to Return
    std::string postfixNotation = "";

    // Stack to hold
    std::stack<char> operatorsStack = std::stack<char>();

    // Loop through every letter of the Infix Notation
    for (size_t index = 0; index < infixNotation.size(); index++)
    {
        char letter = infixNotation[index];

        // If white space
        // ---> skip
        if (letter == ' ')
        {
            continue;
        }

        // If number ---> Add to the result
        else if (std::isdigit(letter))
        {
            postfixNotation += letter;
        }

        // If left parenthesis
        // ---> Add to Stack
        else if (letter == '(')
        {
            operatorsStack.push(letter);
            continue;
        }

        // If Right Parenthesis
        // ---> Pop All the Until there is a Left Parenthesis
        // ---> Add to the Postfix Notation
        else if (letter == ')')
        {
            char infix_operator = operatorsStack.top();

            // Loop until there is a Left Parenthesis in the Stack
            while (infix_operator != '(')
            {
                // Add to the Postfix Notation
                postfixNotation += infix_operator;

                // Pop the stack
                operatorsStack.pop();

                // Move the infix_notation to the next ones in the Stack
                infix_operator = operatorsStack.top();
            }

            // When reach to the Left Parenthesis
            // Pop the last time
            operatorsStack.pop();
        }

        // If Operator
        else if (Operator_Priority_Map.contains(letter))
        {
            // If has no Operator Yet
            // ---> Push into the Stack
            if (operatorsStack.empty())
            {
                operatorsStack.push(letter);
                continue;
            }

            //====================================================================================================
            // If the Priority of the Operator on top the Stack >= current_operator
            // ---> Pop the Operator out of Stack
            // ---> Add to the result
            // ---> Push the current_operator
            //====================================================================================================

            // While the top is still >= current_operator
            // ---> Continuously Add to the Postfix Notation
            // ---> // Then Finally Push the letter in to the Stack
            char top_operator_in_stack;
            while (isOperatorInStack_hasHigherPriority(operatorsStack, letter))
            {
                // Top operator in stack
                top_operator_in_stack = operatorsStack.top();

                // Put into the result Postfix Notation
                postfixNotation += top_operator_in_stack;

                // Pop the Operator
                operatorsStack.pop();
            }

            // If operator in Stack not has Higher Priority
            // ---> Push into Stack
            operatorsStack.push(letter);
        }

        // If Reach the end of the string
        // ---> Pop Every Operator into the Stack
        if (index == infixNotation.size() - 1)
        {
            while (!operatorsStack.empty())
            {
                // Get the Top Operator of the Stack
                char infix_operator = operatorsStack.top();

                // Append to the result Postfix Notation
                postfixNotation += infix_operator;

                // Move to the next operator
                operatorsStack.pop();
            }
        }
    }

    return postfixNotation;
}

//? Function to check if the Priority at the top >= current_operator
bool isOperatorInStack_hasHigherPriority(const std::stack<char> &operatorsStack, char currentOperator)
{
    // If the Stack is Empty
    // ---> No Node left to be Priority
    if (operatorsStack.empty())
    {
        return false;
    }

    // Top operator in stack
    char top_operator_in_stack = operatorsStack.top();

    // Check if Top is Parenthesis to Stop
    if (top_operator_in_stack == '(' || top_operator_in_stack == ')')
    {
        return false;
    }

    return Operator_Priority_Map.at(top_operator_in_stack) >= Operator_Priority_Map.at(currentOperator);
}