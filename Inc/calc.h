#ifndef CALC_H
#define CALC_H

#define MAX 16

// Ngăn xếp cho các toán tử
typedef struct {
    char items[MAX];
    int top;
} OpStack;

void initOpStack(OpStack *s);
void pushOp(OpStack *s, char value);
char popOp(OpStack *s);
char peekOp(OpStack *s);
int isEmptyOp(OpStack *s);

// Ngăn xếp cho các số và hậu tố
typedef struct {
    char items[MAX][MAX];
    int top;
} PostfixStack;

void initPostfixStack(PostfixStack *s);
void pushPostfix(PostfixStack *s, char *value);
char *popPostfix(PostfixStack *s);

int precedence(char op);
int isOperator(char c);

void infixToPostfix(const char *expression, char output[MAX][MAX]);

float applyOp(float a, float b, char op);
float evaluatePostfix(char postfix[MAX][MAX]);
float calc(const char *expression);

#endif // CALC_H
