#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEXEME_SIZE 100
#define MAX_TOKENS 100

// Token types
typedef enum {
    KEYWORD,
    IDENTIFIER,
    DIRECTIVE,
    NUMBER,
    OPERATOR,
    SEPARATOR,
    UNKNOWN
} TokenType;

// Token structure
typedef struct {
    char lexeme[MAX_LEXEME_SIZE];
    TokenType type;
} Token;

// Function to categorize and label lexemes
void categorizeAndLabel(Token token)
{
    switch (token.type) {
        case KEYWORD:
            printf("[kw %s] ", token.lexeme);
            break;
        case IDENTIFIER:
            printf("[id %s] ", token.lexeme);
            break;
        case DIRECTIVE:
            printf("[directive %s] ", token.lexeme);
            break;
        case NUMBER:
            printf("[num %s] ", token.lexeme);
            break;
        case OPERATOR:
            printf("[op %s] ", token.lexeme);
            break;
        case SEPARATOR:
            printf("[sep %s] ", token.lexeme);
            break;
        case UNKNOWN:
            printf("[unkn %s] ", token.lexeme);
            break;
    }
}

// Function to check if a character is a separator
int isSeparator(char ch)
{
    return strchr(";,(){}", ch) != NULL;
}

// Function to check if a character is an operator
int isOperator(char ch)
{
    return strchr("=+-*/", ch) != NULL;
}

// Function to check if a character is a digit
int isDigit(char ch)
{
    return isdigit(ch) || (ch == '.' && isdigit(ch));
}

// Function to tokenize the input
int tokenize(const char *input, Token *tokens)
{
    int num_tokens = 0;
    char lexeme[MAX_LEXEME_SIZE];
    int lexeme_index = 0;

    for (const char *ptr = input; *ptr != '\0'; ptr++) {
        char ch = *ptr;

        if (isspace(ch) || isSeparator(ch) || isOperator(ch)) {
            if (lexeme_index > 0) {
                lexeme[lexeme_index] = '\0';
                strcpy(tokens[num_tokens].lexeme, lexeme);

                if (strcmp(lexeme, "char") == 0 || strcmp(lexeme, "int") == 0 || strcmp(lexeme, "float") == 0 || strcmp(lexeme, "if") == 0 || strcmp(lexeme, "else") == 0 || strcmp(lexeme, "double") == 0) {
                    tokens[num_tokens].type = KEYWORD;
                } else if (strcmp(lexeme, "#include") == 0) {
                    tokens[num_tokens].type = DIRECTIVE;
                } else if (isalpha(lexeme[0]) || lexeme[0] == '_') {
                    tokens[num_tokens].type = IDENTIFIER;
                } else if (isDigit(lexeme[0])) {
                    tokens[num_tokens].type = NUMBER;
                } else {
                    tokens[num_tokens].type = UNKNOWN;
                }

                num_tokens++;
                lexeme_index = 0;
            }

            if (isSeparator(ch)) {
                tokens[num_tokens].lexeme[0] = ch;
                tokens[num_tokens].lexeme[1] = '\0';
                tokens[num_tokens].type = SEPARATOR;
                num_tokens++;
            }

            if (isOperator(ch)) {
                tokens[num_tokens].lexeme[0] = ch;
                tokens[num_tokens].lexeme[1] = '\0';
                tokens[num_tokens].type = OPERATOR;
                num_tokens++;
            }
        } else {
            lexeme[lexeme_index++] = ch;
        }
    }

    return num_tokens;
}

int main(void)
{
    FILE *file;
    char buffer[MAX_LEXEME_SIZE * MAX_TOKENS];
    Token tokens[MAX_TOKENS];

    file = fopen("output.txt", "r");
    if (file == NULL) {
        printf("Error opening input file!!!\n\n");
        return 1;
    } else {
        printf("File opened successfully.\n\n");
    }

    // Read the entire file into buffer
    size_t bytes_read = fread(buffer, sizeof(char), sizeof(buffer), file);
    buffer[bytes_read] = '\0'; // Null-terminate the buffer
    fclose(file);

    // Tokenize the input buffer
    int num_tokens = tokenize(buffer, tokens);

    // Print the categorized tokens
    printf("Categorized Tokens:\n");
    for (int i = 0; i < num_tokens; i++) {
        categorizeAndLabel(tokens[i]);
    }

    return 0;
}
