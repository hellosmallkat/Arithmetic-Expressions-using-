#include <iostream>
#include <stack>
// Function to determine the precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    else if(op == '^')
        return 3;
    return 0;
}
// Function to check if an operator is right-associative
bool rightAssociative(char op) {
    return op == '^';
}
// Function to convert infix expression to postfix expression
std::string infixToPostfix(std::string infixExpression)
{
    std::stack<char> operatorStack;  // Stack to store operators
    std::string postfix;  // Resulting postfix expression

    // Loop through each character in the infix expression
    for (long unsigned int i = 0; i <= infixExpression.length(); i++)
     {
        if (infixExpression[i] == '(')
        {
            // If left parenthesis, push onto the stack
            operatorStack.push(infixExpression[i]);

        }
        else if (infixExpression[i] == '+' || infixExpression[i] == '-' || infixExpression[i] == '*' || infixExpression[i] == '/' || infixExpression[i] == '^')
        {
            // If an operator
            if (infixExpression[i] == '-' && isdigit(infixExpression[i + 1]))
            {
                // Handle negative numbers
                postfix += infixExpression[i];
            }
            else
             {
                // Pop and append operators to the result until the stack is empty or precedence condition is met
                while (!operatorStack.empty() && (precedence(infixExpression[i]) < precedence(operatorStack.top()) || (precedence(infixExpression[i]) == precedence(operatorStack.top()) && !rightAssociative(infixExpression[i]))))
                 {
                    postfix += operatorStack.top();
                    postfix += " ";
                    operatorStack.pop();
                }
                // Push the current operator onto the stack
                operatorStack.push(infixExpression[i]);
            }
        } else if (infixExpression[i] == ')')
         {
            // If right parenthesis, pop and append operators until a left parenthesis is encountered
            while (!operatorStack.empty() && operatorStack.top() != '(')
             {
                postfix += operatorStack.top();
                postfix += " ";
                operatorStack.pop();
             }
            operatorStack.pop(); // Pop the left parenthesis
        }
         else if (isdigit(infixExpression[i]))
        {

for (long unsigned int j = 0; j <= infixExpression.length() - i; j++)
{
        if (isdigit(infixExpression[i + j]))
        {
             postfix += infixExpression[i + j];

        }
        if (!isdigit(infixExpression[i + j]))
        {
            i +=j;
              postfix += " ";
            break;
        }
}
    }

    // Add a space after the complete number

}


    // Pop any remaining operators from the stack
    while (!operatorStack.empty()) {
        postfix += operatorStack.top();
        operatorStack.pop();
        postfix += " ";
    }
     
    return postfix;

}

int main(int argc, char* argv[]) {
    // Check if a valid infix expression is provided as a command line argument
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <infix_expression>" << std::endl;
        return 1;
    }

    // Retrieve infix expression from command line argument
    std::string infixExpression = argv[1];

    // Convert infix to postfix and print the result
    std::string postfixExpression = infixToPostfix(infixExpression);
    std::cout << postfixExpression << std::endl;

    return 0;
}

