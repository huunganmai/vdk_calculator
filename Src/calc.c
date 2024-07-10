#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"


char postfix[MAX][MAX];



void initOpStack(OpStack *s) {
    s->top = -1;
}

void pushOp(OpStack *s, char value) {
    if (s->top < MAX - 1) {
        s->items[++(s->top)] = value;
    }
}

char popOp(OpStack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return '\0';
}

char peekOp(OpStack *s) {
    if (s->top >= 0) {
        return s->items[s->top];
    }
    return '\0';
}

int isEmptyOp(OpStack *s) {
    return s->top == -1;
}

void initPostfixStack(PostfixStack *s) {
    s->top = -1;
}

void pushPostfix(PostfixStack *s, char *value) {
    if (s->top < MAX - 1) {
        strcpy(s->items[++(s->top)], value);
    }
}

char *popPostfix(PostfixStack *s) {
    if (s->top >= 0) {
        return s->items[(s->top)--];
    }
    return NULL;
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case 'x':
        case '/':
            return 2;
    }
    return 0;
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == 'x' || c == '/';
}

void infixToPostfix(const char *expression, char output[MAX][MAX]) {
    OpStack ops;
    initOpStack(&ops);
    PostfixStack outputStack;
    initPostfixStack(&outputStack);

    char numberBuffer[20];
    int j = 0; // Index for numberBuffer

    for (int i = 0; expression[i] != '\0'; i++) {
        if (expression[i] >='0' && expression[i] <= '9') {
            numberBuffer[j++] = expression[i];
        } else if (expression[i] == ' ') {
            continue;
        } else {
            if (j > 0) {
                numberBuffer[j] = '\0';
                pushPostfix(&outputStack, numberBuffer);
                j = 0;
            }

			while (!isEmptyOp(&ops) && precedence(peekOp(&ops)) >= precedence(expression[i])) {
				char op[2] = {popOp(&ops), '\0'};
				pushPostfix(&outputStack, op);
			}
			pushOp(&ops, expression[i]);
        }
    }

    if (j > 0) {
        numberBuffer[j] = '\0';
        pushPostfix(&outputStack, numberBuffer);
    }

    while (!isEmptyOp(&ops)) {
        char op[2] = {popOp(&ops), '\0'};
        pushPostfix(&outputStack, op);
    }

    // Copy the postfix stack to output array
    for (int i = 0; i <= outputStack.top; i++) {
        strcpy(output[i], outputStack.items[i]);
    }
    output[outputStack.top + 1][0] = '\0'; // Null-terminate the output array
}

float applyOp(float a, float b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case 'x': return a * b;
            case '/': return a / b;
        }
        return 0.0;
}

float evaluatePostfix(char postfix[MAX][MAX]) {
        PostfixStack stack;
        initPostfixStack(&stack);

        for (int i = 0; postfix[i][0] != '\0'; i++) {
            if (isOperator(postfix[i][0]) && strlen(postfix[i]) == 1) {
                float b = atof(popPostfix(&stack));
                float a = atof(popPostfix(&stack));
                float result = applyOp(a, b, postfix[i][0]);
                char resultStr[16];
                snprintf(resultStr, 16, "%f", result);
                pushPostfix(&stack, resultStr);
            } else {
                pushPostfix(&stack, postfix[i]);
            }
        }
        return atof(popPostfix(&stack));
}

float calc(const char *expression) {
        infixToPostfix(expression, postfix);
        return evaluatePostfix(postfix);
}
