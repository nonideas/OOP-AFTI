#include "calculator.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int checkBrackets(int openBracket, int closeBracket) {
    if (openBracket == OPEN_BRACKET1 && closeBracket == CLOSE_BRACKET1 ||
        openBracket == OPEN_BRACKET2 && closeBracket == CLOSE_BRACKET2 ||
        openBracket == OPEN_BRACKET3 && closeBracket == CLOSE_BRACKET3) 
    {
        return 1;
    }
	return 0;
}

void initExpr(expr* expr, char* str) {
    expr->str = str;
    expr->pos = 0;
}

void initVariables(variables* var) {
    for (int i = 0; i < 26; ++i) {
        var->variable[i] = 0;
        var->existence[i] = 0;
    }
}

token readPeekToken(expr* expr, int is_peek) {
    token resultToken;
    resultToken.token = -1;
    int fraction = 0;
    int pos = expr->pos;
    while (1) {
        char ch = expr->str[pos];
        if (is_peek) pos++;
        else {
            expr->pos++;
            pos++;
        }
        if (ch == '\0' && resultToken.token == -1) {
            resultToken.token = EOF_TOKEN;
            return resultToken;
        }
        if (ch == '\n' && resultToken.token == -1) {
            resultToken.token = NEW_LINE_TOKEN;
            return resultToken;
        }
        if (ch == '+' && resultToken.token == -1) {
            resultToken.token = PLUS_TOKEN;
            return resultToken;
        }
        if (ch == '-' && resultToken.token == -1) {
            resultToken.token = MINUS_TOKEN;
            return resultToken;
        }
        if (ch == '*' && resultToken.token == -1) {
            resultToken.token = MUL_TOKEN;
            return resultToken;
        }
        if (ch == '/' && resultToken.token == -1) {
            resultToken.token = DIV_TOKEN;
            return resultToken;
        }
        if (ch == '%' && resultToken.token == -1) {
            resultToken.token = DIV_REMAINDER_TOKEN;
            return resultToken;
        }
        if (ch == '#' && resultToken.token == -1) {
            resultToken.token = DIV_WHOLE_TOKEN;
            return resultToken;
        }
        if (ch == '^' && resultToken.token == -1) {
            resultToken.token = POWER_TOKEN;
            return resultToken;
        }
        if (ch == '(' && resultToken.token == -1) {
            resultToken.token = OPEN_BRACKET1;
            return resultToken;
        }
        if (ch == '[' && resultToken.token == -1) {
            resultToken.token = OPEN_BRACKET2;
            return resultToken;
        }
        if (ch == '{' && resultToken.token == -1) {
            resultToken.token = OPEN_BRACKET3;
            return resultToken;
        }
        if (ch == ')' && resultToken.token == -1) {
            resultToken.token = CLOSE_BRACKET1;
            return resultToken;
        }
        if (ch == ']' && resultToken.token == -1) {
            resultToken.token = CLOSE_BRACKET2;
            return resultToken;
        }
        if (ch == '}' && resultToken.token == -1) {
            resultToken.token = CLOSE_BRACKET3;
            return resultToken;
        }
        if (ch == '<' && resultToken.token == -1) {
            resultToken.token = LESS_TOKEN;
            return resultToken;
        }
        if (ch == '>' && resultToken.token == -1) {
            resultToken.token = MORE_TOKEN;
            return resultToken;
        }
        if (ch == '=' && resultToken.token == -1) {
            resultToken.token = EQUALS_TOKEN;
            return resultToken;
        }
        if (ch == ';' && resultToken.token == -1) {
            resultToken.token = SEPARATION_TOKEN;
            return resultToken;
        }
        if (ch == '?' && resultToken.token == -1) {
            resultToken.token = QUESTION_TOKEN;
            return resultToken;
        }
        if (expr->str[pos - 1] == ':' && expr->str[pos] == '=') {
            expr->pos += 1;
            resultToken.token = ASSIGNMENT_TOKEN;
            return resultToken;
        }
        if (ch == ':' && resultToken.token == -1) {
            resultToken.token = COLON_TOKEN;
            return resultToken;
        }

        if ('0' <= ch && ch <= '9') {
            if (resultToken.token == -1) {
                resultToken.token = NUMBER_TOKEN;
                resultToken.value = 0;
            }
            if (fraction == 14) {
                fprintf(stderr, "too large fractional part");
                exit(3);
            }
            if (fraction == 0) {
                resultToken.value = resultToken.value * 10 + (ch - '0');
            }
            else {
                resultToken.value = resultToken.value + (ch - '0') / pow(10, fraction);
                fraction++;
            }
        }
        else if ((ch == ',' || ch == '.') && resultToken.token != -1) {
            fraction = 1;
        }
        else if (resultToken.token != -1) {
            if (is_peek) return resultToken;
            expr->pos -= 1;
            return resultToken;
        }
        else if (ch == ' ' || ch == '\t') {
            continue;
        }

        else if (expr->str[pos - 1] == 'S' && expr->str[pos] == 'I' && expr->str[pos + 1] == 'N' ||
            expr->str[pos - 1] == 's' && expr->str[pos] == 'i' && expr->str[pos + 1] == 'n') {
            expr->pos += 2;
            resultToken.token = SIN_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'C' && expr->str[pos] == 'O' && expr->str[pos + 1] == 'S' ||
            expr->str[pos - 1] == 'c' && expr->str[pos] == 'o' && expr->str[pos + 1] == 's') {
            expr->pos += 2;
            resultToken.token = COS_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'C' && expr->str[pos] == 'O' && expr->str[pos + 1] == 'T' ||
            expr->str[pos - 1] == 'c' && expr->str[pos] == 'o' && expr->str[pos + 1] == 't') {
            expr->pos += 2;
            resultToken.token = COT_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'T' && expr->str[pos] == 'A' && expr->str[pos + 1] == 'N' ||
            expr->str[pos - 1] == 't' && expr->str[pos] == 'a' && expr->str[pos + 1] == 'n') {
            expr->pos += 2;
            resultToken.token = TAN_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'A' && expr->str[pos] == 'B' && expr->str[pos + 1] == 'S' ||
            expr->str[pos - 1] == 'a' && expr->str[pos] == 'b' && expr->str[pos + 1] == 's') {
            expr->pos += 2;
            resultToken.token = ABS_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'E' && expr->str[pos] == 'X' && expr->str[pos + 1] == 'P' ||
            expr->str[pos - 1] == 'e' && expr->str[pos] == 'x' && expr->str[pos + 1] == 'p') {
            expr->pos += 2;
            resultToken.token = EXP_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'L' && expr->str[pos] == 'O' && expr->str[pos + 1] == 'G' ||
            expr->str[pos - 1] == 'l' && expr->str[pos] == 'o' && expr->str[pos + 1] == 'g') {
            expr->pos += 2;
            resultToken.token = LOG_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'S' && expr->str[pos] == 'Q' && expr->str[pos + 1] == 'R' && expr->str[pos + 2] == 'T' ||
            expr->str[pos - 1] == 's' && expr->str[pos] == 'q' && expr->str[pos + 1] == 'r' && expr->str[pos + 2] == 't') {
            expr->pos += 3;
            resultToken.token = SQRT_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'E' && expr->str[pos] == 'P' && expr->str[pos + 1] == 'S') {
            expr->pos += 2;
            resultToken.token = EPSILON_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'M' && expr->str[pos] == '_' && expr->str[pos + 1] == 'E') {
            expr->pos += 2;
            resultToken.token = M_E_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'M' && expr->str[pos] == '_' && expr->str[pos + 1] == 'P' &&
            expr->str[pos + 2] == 'I') {
            expr->pos += 3;
            resultToken.token = M_PI_TOKEN;
            return resultToken;
        }
        else if (expr->str[pos - 1] == 'I' && expr->str[pos] == 'F' ||
            expr->str[pos - 1] == 'i' && expr->str[pos] == 'f') {
            expr->pos += 1;
            resultToken.token = CONDITION_TOKEN;
            return resultToken;
        }
        else if ('a' <= ch && ch <= 'z') {
            resultToken.token = VARIABLE_TOKEN;
            resultToken.value = ch - 'a';
            return resultToken;
        }
        else {
            fprintf(stderr, "unknown symbol or operation");
            exit(8);
        }
    }
}

double parseVariables(expr* expr, variables* var) {
    int pos = expr->pos;
    token resultToken = readPeekToken(expr, 0);
    token assignment = readPeekToken(expr, 0);
    while (resultToken.token == VARIABLE_TOKEN && assignment.token == ASSIGNMENT_TOKEN) {
        double res = parseExpr(expr, var);
        var->variable[(int)resultToken.value] = res;
        var->existence[(int)resultToken.value] = 1;
        token nextLine = readPeekToken(expr, 0);
        if (nextLine.token != NEW_LINE_TOKEN && nextLine.token != SEPARATION_TOKEN) {
            fprintf(stderr, "incorrect symbol or operation");
            exit(6);
        }

        pos = expr->pos;
        resultToken = readPeekToken(expr, 0);
        assignment = readPeekToken(expr, 0);
    }
    expr->pos = pos;
    double res = parseExpr(expr, var);
    return res;
}

double parseExpr(expr* expr, variables* var) {
    double res = parseMonome(expr, var);
    token resultToken = readPeekToken(expr, 1);
    while (resultToken.token == PLUS_TOKEN || resultToken.token == MINUS_TOKEN) {
        readPeekToken(expr, 0);
        double add = parseMonome(expr, var);
        if (resultToken.token == PLUS_TOKEN)
            res += add;
        else
            res -= add;
        resultToken = readPeekToken(expr, 1);
    }
    return res;
}

double parseMonome(expr* expr, variables* var) {
    double res = parsePower(expr, var);
    token resultToken = readPeekToken(expr, 1);
    while (resultToken.token == MUL_TOKEN || resultToken.token == DIV_TOKEN
        || resultToken.token == DIV_REMAINDER_TOKEN || resultToken.token == DIV_WHOLE_TOKEN) {
        readPeekToken(expr, 0);
        double coef = parsePower(expr, var);
        if (resultToken.token == MUL_TOKEN)
            res *= coef;
        else if (resultToken.token == DIV_TOKEN) {
            if (coef == 0) {
                fprintf(stderr, "division by zero");
                exit(2);
            }
            res /= coef;
        }
        else if (resultToken.token == DIV_REMAINDER_TOKEN) {
            if (coef == 0) {
                fprintf(stderr, "division by zero");
                exit(2);
            }
            if (coef == floor(coef) && res == floor(res))
                res = (int32_t)res % (int32_t)coef;
            else {
                fprintf(stderr, "modulo division by not an integer");
                exit(2);
            }
        }
        else {
            if (coef == 0) {
                fprintf(stderr, "division by zero");
                exit(2);
            }
            if (coef == floor(coef) && res == floor(res))
                res = floor(res / coef);
            else {
                fprintf(stderr, "modulo division by not an integer");
                exit(2);
            }
        }
        resultToken = readPeekToken(expr, 1);
    }
    return res;
}

double parsePower(expr* expr, variables* var) {
    double res = parseAtom(expr, var);
    token resultToken = readPeekToken(expr, 1);
    while (resultToken.token == POWER_TOKEN) {
        readPeekToken(expr, 0);
        double power = parseAtom(expr, var);
        res = pow(res, power);
        resultToken = readPeekToken(expr, 1);
    }
    return res;
}

double parseAtom(expr* expr, variables* var) {
    token resultToken = readPeekToken(expr, 0);
    if (resultToken.token == OPEN_BRACKET1 || resultToken.token == OPEN_BRACKET2 ||
        resultToken.token == OPEN_BRACKET3) {
        double res = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(resultToken.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return res;
    }
    else if (resultToken.token == SIN_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return sin(res);
    }
    else if (resultToken.token == COS_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return cos(res);
    }
    else if (resultToken.token == COT_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return 1 / tan(res);
    }
    else if (resultToken.token == TAN_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return tan(res);
    }
    else if (resultToken.token == ABS_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return fabs(res);
    }
    else if (resultToken.token == EXP_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return exp(res);
    }
    else if (resultToken.token == LOG_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        if (res <= 0) {
            fprintf(stderr, "incorrect taking of the logarithm");
            exit(2);
        }
        token separation = readPeekToken(expr, 0);
        if (separation.token != SEPARATION_TOKEN) {
            fprintf(stderr, "incorrect symbol or operation");
            exit(6);
        }
        double base = parseExpr(expr, var);
        if (base <= 0 || base == 1) {
            fprintf(stderr, "incorrect taking of the logarithm");
            exit(2);
        }
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return log(res) / log(base);
    }
    else if (resultToken.token == SQRT_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double res = parseExpr(expr, var);
        if (res < 0) {
            fprintf(stderr, "incorrect taking of the sqrt");
            exit(2);
        }
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        return sqrt(res);
    }
    else if (resultToken.token == CONDITION_TOKEN) {
        token openBracket = readPeekToken(expr, 0);
        double cond1 = parseExpr(expr, var);
        token condition = readPeekToken(expr, 0);
        if (condition.token != MORE_TOKEN && condition.token != LESS_TOKEN && condition.token != EQUALS_TOKEN) {
            fprintf(stderr, "incorrect symbol or operation");
            exit(6);
        }
        double cond2 = parseExpr(expr, var);
        token question = readPeekToken(expr, 0);
        if (question.token != QUESTION_TOKEN) {
            fprintf(stderr, "incorrect symbol or operation");
            exit(6);
        }
        double res1 = parseExpr(expr, var);
        token colon = readPeekToken(expr, 0);
        if (colon.token != COLON_TOKEN) {
            fprintf(stderr, "incorrect symbol or operation");
            exit(6);
        }
        double res2 = parseExpr(expr, var);
        token closeBracket = readPeekToken(expr, 0);
        if (!checkBrackets(openBracket.token, closeBracket.token)) {
            fprintf(stderr, "wrong balance of brackets");
            exit(5);
        }
        if (condition.token == LESS_TOKEN) {
            if (cond1 < cond2) return res1;
            return res2;
        }
        if (condition.token == MORE_TOKEN) {
            if (cond1 > cond2) return res1;
            return res2;
        }
        if (cond1 == cond2) return res1;
        return res2;
    }
    if (resultToken.token == EPSILON_TOKEN) {
        return EPSILON;
    }
    if (resultToken.token == M_PI_TOKEN) {
        return M_PI;
    }
    if (resultToken.token == M_E_TOKEN) {
        return M_E;
    }
    if (resultToken.token == MINUS_TOKEN) {
        resultToken = readPeekToken(expr, 0);
        double res;
        if (resultToken.token == OPEN_BRACKET1 || resultToken.token == OPEN_BRACKET2 ||
            resultToken.token == OPEN_BRACKET3) {
            res = parseExpr(expr, var);
            token closeBracket = readPeekToken(expr, 0);
            if (!checkBrackets(resultToken.token, closeBracket.token)) {
                fprintf(stderr, "wrong balance of brackets");
                exit(5);
            }
        }
        else {
            res = resultToken.value;
        }
        return -1 * res;
    }
    if (resultToken.token == NUMBER_TOKEN) {
        return resultToken.value;
    }
    if (resultToken.token == VARIABLE_TOKEN) {
        if (var->existence[(int)resultToken.value] == 1) {
            return var->variable[(int)resultToken.value];
        }
        else {
            fprintf(stderr, "using an uninitialized variable");
            exit(4);
        }
    }
    else {
        fprintf(stderr, "incorrect expression");
        exit(7);
    }
}