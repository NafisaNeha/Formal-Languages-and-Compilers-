#include <stdio.h>
#include <string.h>
#include <ctype.h>

int keyword(char str[])
{
    const char *keywords[] = {"auto", "double", "int", "struct", "break", "else", "long", "switch",
                              "case", "enum", "register", "typedef", "char", "extern", "return",
                              "union", "continue", "for", "signed", "void", "do", "if", "static",
                              "while", "default", "goto", "sizeof", "volatile", "const", "float",
                              "short", "unsigned"
                             };
    for (int i = 0; i < sizeof(keywords) / sizeof(keywords[0]); i++)
    {
        if (strcmp(str, keywords[i]) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int identifier(char str[])
{
    if (!isalpha(str[0]) && str[0] != '_')
    {
        return 0;
    }
    for (int i = 1; str[i] != '\0'; i++)
    {
        if (!isalnum(str[i]) && str[i] != '_')
        {
            return 0;
        }
    }
    return 1;
}

int is_operator(char c)
{
    const char operators[] = "+-*/%=!<>|&";
    for (int i = 0; operators[i] != '\0'; i++)
    {
        if (c == operators[i])
        {
            return 1;
        }
    }
    return 0;
}

int is_separator(char c)
{
    const char separators[] = "',;\"";
    for (int i = 0; separators[i] != '\0'; i++)
    {
        if (c == separators[i])
        {
            return 1;
        }
    }
    return 0;
}

int is_parenthesis(char c)
{
    return (c == '(' || c == ')');
}

int is_number(const char *str)
{
    int i = 0;
    if (str[i] == '-' || str[i] == '+')
    {
        i++;
    }
    while (str[i] != '\0')
    {
        if (!isdigit(str[i]) && str[i] != '.')
        {
            return 0;
        }
        if (str[i] == '.' && !isdigit(str[i + 1]))
        {
            return 0;
        }
        i++;
    }
    return 1;
}

int main()
{
    FILE *file;
    file = fopen("output.txt", "r");

    char c;
    if (file== NULL)
        printf("Error opening file!!!\n\n");
    else
        printf("File opened successfully.\n\n");

    printf("Filtered File from output.txt:\n");
    while ((c = fgetc(file)) != EOF)
    {
        printf("%c", c);
    }
    printf("\n\n");
    char lexeme[50];
    int state = 0;

    while (1)
    {
        int c = fgetc(file);
        if (c == EOF)
        {
            break;
        }

        if (isspace(c))
        {
            if (state)
            {
                lexeme[state] = '\0';
                fprintf(file, " %s ", lexeme);
                state = 0;
            }
        }
        else if (is_operator(c) || is_separator(c) || is_parenthesis(c))
        {
            if (state)
            {
                lexeme[state] = '\0';
                fprintf(file, " %s ", lexeme);
                state = 0;
            }
            fprintf(file, " %c ", c);
        }
        else
        {
            lexeme[state++] = c;
        }
    }

    fclose(file);


    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }


    fclose(file);


    return 0;
}
