#include <stdio.h>
#include <stdlib.h>

void Exp();
void Term();
void Factor();
void match(char symbol);

void error()
{
    printf("Invalid expression\n");
    exit(1);
}

void Exp()
{
    Term();
    while (1)
    {
        char op = getchar();
        if (op == '+' || op == '-')
        {
            Term();
        }
        else
        {
            ungetc(op, stdin);
            break;
        }
    }
}

void Term()
{
    Factor();
    while (1)
    {
        char op = getchar();
        if (op == '*' || op == '/')
        {
            Factor();
        }
        else
        {
            ungetc(op, stdin);
            break;
        }
    }
}

void Factor()
{
    char symbol = getchar();
    if (symbol == '(')
    {
        Exp();
        match(')');
    }
    else if ((symbol >= 'a' && symbol <= 'e') || (symbol >= '0' && symbol <= '9'))
    {
        // Valid symbol
    }
    else
    {
        error();
    }
}

void match(char symbol)
{
    char input;
    scanf(" %c", &input);
    if (input != symbol)
    {
        error();
    }
}

int main()
{
    printf("Enter the string: ");
    Exp();

    if (getchar() != '\n')
    {
        error();
    }

    printf("Valid expression\n");

    return 0;
}
