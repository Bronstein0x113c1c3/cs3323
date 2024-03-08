#include <iostream>
#include <stack>
#include <cctype>
#include <string>
#include <unordered_map>
#include <format>
#include <cmath>


const std::unordered_map<char, int> Operator_Priority_Map = {
    {'^', 3},
    {'*', 2},
    {'/', 2},
    {'+', 1},
    {'-', 1}};

const char separator = '|';

bool isOperatorInStack_hasHigherPriority(const std::stack<char> &operatorsStack, char currentOperator);
double doMath(double firstNum, double lastNum, char operator_char);

//! Some Limit: Cannot work with nested Parenthesis (Ex: ((1 + 2) – 3 * (4 / 5)) + 6 )
std::string infixToPostfixNotation(const std::string &infixNotation);

bool isPostfixExpression(const std::string &postfixToEvaluate);

double getPostfixResult(const std::string &postfixNotation);

int main(int argc, char const *argv[])
{
    // Try to Convert the Infix Notation --> Postfix Notation
    std::cout << "===============================================================" << std::endl;
    std::string infixNotation = "( 9 - 5 ) ^ 3 + 7 * 8";
    std::string postfixNotation = infixToPostfixNotation(infixNotation);

    std::cout << "Infix Notation: "
              << infixNotation
              << std::endl;

    std::cout << "Postfix Notation: "
              << postfixNotation
              << std::endl;

    // Try to Check if that postfix is Valid
    std::cout << "===============================================================" << std::endl;
    std::string postfixToEvaluate = postfixNotation;
    bool isPostfix = isPostfixExpression(postfixToEvaluate);
    std::cout << std::format(
        "{} {} a Postfix Notation!\n",
        postfixToEvaluate,
        (isPostfix) ? "is" : "is not");

    // Check if the Postfix is valid before do math
    if (!isPostfix)
    {
        return 1;
    }
    // Try to do math with postfix
    std::cout << "===============================================================" << std::endl;
    int result = getPostfixResult(postfixNotation);
    std::cout << std::format(
        "{} is {}\n",
        infixNotation,
        result
    );

    return 0;
}

/// @brief Take an Infix Notation transfer to Postfix Notation
/// @param infixNotation Infix Notation Input
/// @return Postfix Notation
std::string infixToPostfixNotation(const std::string &infixNotation)
{
    // Postfix Notation to Return
    std::string postfixNotation = "";

    // TODO: Maybe use | to separate the operand and the operator

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
                postfixNotation += separator; // Add separator
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
            // Use '|' to separate each operand and operator
            postfixNotation += separator;

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
                // Top operator_char in stack
                top_operator_in_stack = operatorsStack.top();

                // Put into the result Postfix Notation
                postfixNotation += top_operator_in_stack;
                postfixNotation += separator; // Add separator

                // Pop the Operator
                operatorsStack.pop();
            }

            // If operator_char in Stack not has Higher Priority
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
                postfixNotation += separator; // Add separator
                postfixNotation += infix_operator;

                // Move to the next operator_char
                operatorsStack.pop();
            }

            // Add the last separator
            postfixNotation += separator; // Add separator
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

    // Top operator_char in stack
    char top_operator_in_stack = operatorsStack.top();

    // Check if Top is Parenthesis to Stop
    if (top_operator_in_stack == '(' || top_operator_in_stack == ')')
    {
        return false;
    }

    return Operator_Priority_Map.at(top_operator_in_stack) >= Operator_Priority_Map.at(currentOperator);
}

bool isPostfixExpression(const std::string &postfixToEvaluate)
{
    // Return Value
    bool isPostfix = false;

    // Check if First Character is Valid ?
    char firstCharacter = postfixToEvaluate[0];
    if (!std::isdigit(firstCharacter)) // Not a digit --> Return False
    {
        return isPostfix;
    }

    // Stack of Operands to Evaluate
    std::stack<double *> operandsStack = std::stack<double *>();

    // ==================================================
    // Find the first Number
    double first_num = 0.0;
    std::string first_num_str;
    int start_index = 0;
    int end_index = start_index;

    char letter = postfixToEvaluate[start_index];
    while (letter != separator)
    {
        // Move to the next letter
        end_index++;

        // Get the character at that position
        letter = postfixToEvaluate[end_index];
    }

    // Push the First Number into the stack
    first_num_str = postfixToEvaluate.substr(start_index, end_index);

    first_num = std::stod(first_num_str);
    operandsStack.push(&first_num);

    // First Operand Memory to check
    double *firstOperand = &first_num;

    // Loop through the postfix Notation
    // If Operand --> Push to the Stack
    // If Operator --> Pop the first
    for (size_t index = end_index; index < postfixToEvaluate.size(); index++)
    {
        // Letter to check
        char letter = postfixToEvaluate[index];

        // If Operand --> Push to the Stack
        if (std::isdigit(letter))
        {
            // The num to get
            double num = 0.0;
            std::string num_str;

            // Start index, End index to track
            int start_index = 0;

            // Continue loop until find a separator '|'
            while (letter != separator)
            {
                // Move to the next index
                index++;

                // Get the character at that index
                letter = postfixToEvaluate[index];
            }

            // Push to the Stack
            num_str = postfixToEvaluate.substr(start_index, index);
            num = std::stod(num_str);
            operandsStack.push(&num);
        }

        // If Operator --> Pop the first element
        else if (Operator_Priority_Map.contains(letter))
        {
            operandsStack.pop();
        }
    }

    // Left the final character in the stack
    // --> That &final_character == &first_operand

    // Get the final character
    double *finalOperand = operandsStack.top();
    isPostfix = (finalOperand == firstOperand);

    return isPostfix;
}

/// @brief Do some math to return the Result of the Postfix Notation
/// @param postfixNotation
/// @return result
double getPostfixResult(const std::string &postfixNotation)
{
    // Result To return
    double result = 0;

    // Operand Stack to hold
    std::stack<double> operandStack = std::stack<double>();

    // ============================================================
    // Loop through the Postfix Notation
    // If letter == operand:
    // ---> Push into the Stack
    // If letter == operator_char:
    // ---> Pop the top 2 element in the Stack
    // ---> Apply the Mathematic Operation to the 2 elements
    // ---> Push back the Result
    // ===========================================================
    // Finished
    // ---> Result = Pop the Stack last time
    // ---> return Result

    // Loop through the Postfix Notation
    for (size_t index = 0; index < postfixNotation.size(); index++)
    {
        // Get the Character
        char letter = postfixNotation[index];

        // If Operand
        // ---> Push to the Stack
        if (std::isdigit(letter))
        {
            // Number to calculate result
            double num = 0.0;

            // Start index
            int start_index = index;

            // Continue until find the '|'
            while (letter != separator)
            {
                // Move to the next index
                index++;

                // Get the character at that position
                letter = postfixNotation[index];
            }

            // Operand to push
            std::string first_num_str = postfixNotation.substr(start_index, index);
            num = std::stod(first_num_str);
            operandStack.push(num);
        }

        // If Operator
        // ---> Pop the top 2 element in the Stack
        // ---> Apply the Mathematic Operation to the 2 elements
        // ---> Push back the Result
        else if (Operator_Priority_Map.contains(letter))
        {
            // Pop the top 2 element out of Stack
            int lastNum = operandStack.top();
            operandStack.pop();

            int firstNum = operandStack.top();
            operandStack.pop();

            // Apply the Arithmetic Operation
            int result_of_first_last = doMath(firstNum, lastNum, letter);

            // Push back the result back to the Stack
            operandStack.push(result_of_first_last);
        }
    }

    // Loop Finished
    // ---> Pop the Stack to get Result
    result = operandStack.top();
    operandStack.pop();

    return result;
}

double doMath(double firstNum, double lastNum, char operator_char)
{
    // Result to return
    double result = 0.0;

    switch (operator_char)
    {
    case '+':
        result = firstNum + lastNum;
        break;
    case '-':
        result = firstNum - lastNum;
        break;
    case '*':
        result = firstNum * lastNum;
        break;
    case '/':
        result = firstNum / lastNum;
        break;
    case '^':
        result = std::pow(firstNum, lastNum);
        break;
    default:
        std::cerr << "Invalid Operator: " << operator_char << std::endl;
        break;
    }

    return result;
}