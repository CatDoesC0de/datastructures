#include <print>
#include <stack>
#include <string>
#include <sstream>

using std::println;

int get_precedence(char op)
{
    switch (op)
    {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return -1;
    }
}

bool is_whitespace(char character)
{
    return character == ' ' || character == '\t' || character == '\n';
}

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        println("[Usage]: {} <expression>", argv[0]);
        return -1;
    }

    std::string infix = argv[1];
    std::stringstream postfix;
    std::stack<char> stack;

    for (size_t i = 0; i < infix.size(); i++)
    {
        char symbol = infix[i];
        if (is_whitespace(symbol))
        {
            continue;
        }

        switch (symbol)
        {
            case '(': 
                stack.push(symbol);
                break;
            case ')':
            {
                while (stack.top() != '(')
                {
                    postfix << stack.top() << ' ';
                    stack.pop();
                }

                stack.pop(); // Pop left parenthesis
                break;
            }

            case '+':
            case '-':
            case '/':
            case '*':
            {
                
                // Make sure stack isn't empty before calling top()
                while (!stack.empty() && stack.top() != '(') 
                {
                    char popped_operator = stack.top();
                    int operator_precedence = get_precedence(popped_operator);
                    stack.pop();

                    if (get_precedence(symbol) >= operator_precedence)
                    {
                        postfix << popped_operator << ' ';
                    }
                }

                stack.push(symbol);
                break;
            }

            default:
                postfix << symbol << ' ';
        }
    }

    while (!stack.empty())
    {
        postfix << stack.top() << ' ';
        stack.pop();
    }

    println("{}", postfix.view());
}
