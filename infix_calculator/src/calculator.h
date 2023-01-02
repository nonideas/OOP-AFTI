#pragma once

// input string length
#define N (100 * 1000)

// each character or set of characters corresponds to a token
#define PLUS_TOKEN (1)
#define MINUS_TOKEN (2)
#define MUL_TOKEN (3)
#define DIV_TOKEN (4)
#define DIV_REMAINDER_TOKEN (5)
#define DIV_WHOLE_TOKEN (6)
#define POWER_TOKEN (7)
#define SIN_TOKEN (8)
#define COS_TOKEN (9)
#define TAN_TOKEN (10)
#define COT_TOKEN (11)
#define SQRT_TOKEN (12)
#define LOG_TOKEN (13)
#define EXP_TOKEN (14)
#define ABS_TOKEN (15)
#define OPEN_BRACKET1 (16)
#define OPEN_BRACKET2 (17)
#define OPEN_BRACKET3 (18)
#define CLOSE_BRACKET1 (19)
#define CLOSE_BRACKET2 (20)
#define CLOSE_BRACKET3 (21)
#define M_PI_TOKEN (22)
#define M_E_TOKEN (23)
#define EPSILON_TOKEN (24)
#define SEPARATION_TOKEN (25)
#define CONDITION_TOKEN (26)
#define LESS_TOKEN (27)
#define MORE_TOKEN (28)
#define EQUALS_TOKEN (29)
#define QUESTION_TOKEN (30)
#define COLON_TOKEN (31)
#define NUMBER_TOKEN (32)
#define VARIABLE_TOKEN (33)
#define ASSIGNMENT_TOKEN (34)
#define NEW_LINE_TOKEN (35)
#define EOF_TOKEN (36)

#define EPSILON ((double)1/1000/1000/1000/1000)

// stores the token of the character read and the value if the token is a number or a variable
typedef struct {
    int token;
    double value;
} token;

// stores the string and a pointer to the character of the string during parsing
typedef struct {
    char* str;
    int pos;
} expr;

// stores the state of the variables (1 - used, 0 - not used) and the value of the used variables from a to z
typedef struct {
    double variable[26];
    int existence[26];
} variables;

// function to check the correct placement of brackets
int checkBrackets(int openBracket, int closeBracket);

// function to initialize the expression structure
void initExpr(expr* expr, char* str);

// function to initialize the variable structure
void initVariables(variables* var);

// function reads a character or set of characters and assigns a token to those characters
token readPeekToken(expr* expr, int is_peek);

// function parsing a string to assign values to variables or evaluate the value of the final expression
double parseVariables(expr* expr, variables* var);

// function for addition and subtraction
double parseExpr(expr* expr, variables* var);

// function for multiplication and division (different types)
double parseMonome(expr* expr, variables* var);

// function for raising a number to a power
double parsePower(expr* expr, variables* var);

// function for parsing a number, a variable, an expression in brackets or function of an expression in brackets
double parseAtom(expr* expr, variables* var);