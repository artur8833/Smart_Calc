#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void parcer(char *str,double x);
void to_number(char *str, double *num);

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

typedef struct stack {
  double num;
  int priority;
  int type;
  struct stack *next_operators;
} stack;


#endif