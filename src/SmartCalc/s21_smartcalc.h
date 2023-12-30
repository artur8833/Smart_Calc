#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define ERROR 1

typedef struct stack {
    double num;
    int priority;
    int type;
    char symbol;
    struct stack *next_operators;
} stack;


double s21_calculator(char *str,double x);
int char_is_number(char c);
void parcer(char *str,stack **head_stack,double x);
void append(stack ** phead, double num, int priority,int type,char symbol);
double pop(stack **phead);
void parce_operators (char *str,int *i, stack **head);
void convert_in_RPN(stack **head, stack **result);
void removeStack(stack** support, stack** head , int current_priority);
double calculation(stack **rpn);
stack *reverse_stack(stack *original);
double calculate(double a1, double a2, char symb);
void to_number(char *str, double *num);

int validation(char *str);
int incorrect_fuc(char *str);
int incorrect_brackets(char *str);
int incorrect_dot(char *str);
int incorrect_signs(char *str);

enum types {
    NUMBERS=0,
    PLUS=1,
    MINUS=2,
    MULT=3,
    DIV=4,
    MOD=5,
    EXP=6,
    BRAC_OPEN=7,
    BRAC_CLOSE=8,
    COS=9,
    SIN=10,
    TAN=11,
    ATAN=12,
    ACOS=13,
    ASIN=14,
    SQRT=15,
    LN=16,
    LOG=17
};



#endif
