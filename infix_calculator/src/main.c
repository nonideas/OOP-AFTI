#include "calculator.h"
#include <stdio.h>

char str[N];

int main() {
    printf("enter expression (finish expression !):\n");
    scanf(" %[^!]s", str);

    expr expr;
    variables var;
    initExpr(&expr, str);
    initVariables(&var);
    double res = parseVariables(&expr, &var);
    printf("%.13lf\n", res);

    char ch;
    scanf("%c", &ch);

    return 0;
}