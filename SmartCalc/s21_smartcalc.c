#include "s21_smartcalc.h"

void print(stack *head) {
  for (stack *p = head; p != NULL; p = p->next_operators) {
    printf("%f ", p->num);
    printf("%d ", p->priority);
    printf("%d ", p->type);
    printf("%c", p->symbol);
    printf("| ");
  }
  printf("\n");
}

void append(stack **phead, double num, int priority, int type, char symbol) {
  stack *p = malloc(sizeof(stack));
  p->priority = priority;
  p->num = num;
  p->type = type;
  p->symbol = symbol;
  p->next_operators = *phead;
  *phead = p;
}

double pop(stack **phead) {
  stack *p = *phead;
  *phead = p->next_operators;
  free(p);
  return 0;
}

double s21_calculator(char *str, double x) {
  stack *head_stack = NULL;
  stack *rpn = NULL;
  double result = 0;
  if (strlen(str) != 0) {
    parcer(str, &head_stack, x);
    convert_in_RPN(&head_stack, &rpn);
    result = calculation(&rpn);
  }
  return result;
}

void parcer(char *str, stack **head_stack, double x) {
  char numbers_buf[255] = "";
  char operators_mas[] = "+-*/^mcstal()";
  int len = strlen(str);
  int j = 0;
  double num = 0;
  for (int i = 0; i < len; i++) {
    while (char_is_number(str[i])) {
      numbers_buf[j] = str[i];
      j++;
      i++;
    }
    if (!char_is_number(str[i]) && j > 0) {
      to_number(numbers_buf, &num);
      append(head_stack, num, 0, NUMBERS, ' ');
      memset(&numbers_buf, 0, sizeof(numbers_buf));
      j = 0;
    }
    if (str[i] == 'x' || str[i] == 'X') {
      append(head_stack, x, 0, NUMBERS, ' ');
    }

    if (strchr(operators_mas, str[i]) != NULL) {
      parce_operators(str, &i, head_stack);
    }
  }
}

void parce_operators(char *str, int *i, stack **head) {
  if (str[*i] == '+') {
    append(head, 0, 1, PLUS, '+');
  }
  if (str[*i] == '-') {
    append(head, 0, 1, MINUS, '-');
  }
  if (str[*i] == '*') {
    append(head, 0, 2, MULT, '*');
  }
  if (str[*i] == '/') {
    append(head, 0, 2, DIV, '/');
  }
  if (str[*i] == '^') {
    append(head, 0, 3, EXP, '^');
  }
  if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') {
    *i = *i + 2;
    append(head, 0, 3, MOD, 'm');
  }
  if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's') {
    *i = *i + 2;
    append(head, 0, 4, COS, 'c');
  }
  if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n') {
    *i = *i + 2;
    append(head, 0, 4, SIN, 's');
  }
  if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n') {
    *i = *i + 2;
    append(head, 0, 4, TAN, 't');
  }
  if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's') {
    *i = *i + 3;
    append(head, 0, 4, ACOS, 'C');
  }
  if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
      str[*i + 3] == 'n') {
    *i = *i + 3;
    append(head, 0, 4, ASIN, 'S');
  }
  if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
      str[*i + 3] == 'n') {
    *i = *i + 3;
    append(head, 0, 4, ATAN, 'T');
  }
  if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
      str[*i + 3] == 't') {
    *i = *i + 3;
    append(head, 0, 4, SQRT, 'Q');
  }
  if (str[*i] == 'l' && str[*i + 1] == 'n') {
    *i = *i + 1;
    append(head, 0, 4, LN, 'L');
  }
  if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g') {
    *i = *i + 2;
    append(head, 0, 4, LOG, 'g');
  }
  if (str[*i] == '(') {
    append(head, 0, 1, BRAC_OPEN, '(');
  }
  if (str[*i] == ')') {
    append(head, 0, 1, BRAC_CLOSE, ')');
  }
}

void convert_in_RPN(stack **head, stack **result) {
  stack *reverses_stack = reverse_stack(*head);
  stack *support = NULL;
  while (reverses_stack != NULL) {
    if (reverses_stack->type == 0) {
      append(result, reverses_stack->num, reverses_stack->priority,
             reverses_stack->type, reverses_stack->symbol);
      pop(&reverses_stack);
    } else if ((*result == NULL) && (reverses_stack->symbol == '-')) {
      append(result, 0, 0, NUMBERS, ' ');
    } else {
      if (support == NULL) {
        append(&support, reverses_stack->num, reverses_stack->priority,
               reverses_stack->type, reverses_stack->symbol);
        pop(&reverses_stack);
      } else if (reverses_stack->type != 8) {
        if ((reverses_stack->symbol == '(') &&
            (reverses_stack->next_operators->symbol == '-')) {
          append(result, 0, 0, NUMBERS, ' ');
        }

        append(&support, reverses_stack->num, reverses_stack->priority,
               reverses_stack->type, reverses_stack->symbol);
        pop(&reverses_stack);

        if ((support->type != 7)) {
          removeStack(&support->next_operators, result, support->priority);
        }
      } else if (reverses_stack->type == 8) {
        pop(&reverses_stack);
        while ((support != NULL)) {
          if (support->type == 7) {
            pop(&support);
            break;
          }

          append(result, support->num, support->priority, support->type,
                 support->symbol);
          pop(&support);
        }
      }
    }
  }

  while (support != NULL) {
    append(result, support->num, support->priority, support->type,
           support->symbol);
    pop(&support);
  }
}

void removeStack(stack **support, stack **head, int current_priority) {
  stack *current = *support;
  stack *previous = NULL;
  while ((current != NULL) && (current->type != 7)) {
    if ((current->priority >= current_priority) && (current->type != 7)) {
      if (previous == NULL) {
        stack *next = current->next_operators;
        append(head, current->num, current->priority, current->type,
               current->symbol);
        pop(&current);
        *support = next;
        current = next;
      } else {
        stack *next = current->next_operators;
        append(head, current->num, current->priority, current->type,
               current->symbol);
        pop(&current);
        previous->next_operators = next;
        current = next;
      }
    } else {
      previous = current;
      current = current->next_operators;
    }
  }
}

stack *reverse_stack(stack *original) {
  stack *reverse = NULL;
  while (original != NULL) {
    append(&reverse, original->num, original->priority, original->type,
           original->symbol);
    pop(&original);
  }
  return reverse;
}

double calculation(stack **rpn) {
  stack *rpn_reverse_stack = reverse_stack(*rpn);
  stack *support = NULL;
  double n1, n2, res = 0;

  while (rpn_reverse_stack != NULL) {
    if (rpn_reverse_stack->type == 0) {
      append(&support, rpn_reverse_stack->num, rpn_reverse_stack->priority,
             rpn_reverse_stack->type, rpn_reverse_stack->symbol);
      pop(&rpn_reverse_stack);
    } else {
      if ((rpn_reverse_stack->priority == 1) ||
          (rpn_reverse_stack->priority == 2) ||
          (rpn_reverse_stack->priority == 3)) {
        n2 = support->num;
        pop(&support);
        n1 = support->num;
        pop(&support);
        res = calculate(n1, n2, rpn_reverse_stack->symbol);
        append(&support, res, 0, NUMBERS, ' ');
        pop(&rpn_reverse_stack);
      } else if (rpn_reverse_stack->priority == 4) {
        n1 = support->num;
        pop(&support);
        res = calculate(n1, 0, rpn_reverse_stack->symbol);
        append(&support, res, 0, NUMBERS, ' ');
        pop(&rpn_reverse_stack);
      }
    }
  }
  if (support != NULL) {
    res = support->num;
    pop(&support);
  }
  return res;
}

double calculate(double a1, double a2, char symb) {
  double result = 0;
  if (symb == '+') {
    result = a1 + a2;
  } else if (symb == '-') {
    result = a1 - a2;
  } else if (symb == '*') {
    result = a1 * a2;
  } else if (symb == '/') {
    result = a1 / a2;
  } else if (symb == '^') {
    result = pow(a1, a2);
  } else if (symb == 'm') {
    result = fmod(a1, a2);
  } else if (symb == 'c') {
    result = cos(a1);
  } else if (symb == 's') {
    result = sin(a1);
  } else if (symb == 't') {
    result = tan(a1);
  } else if (symb == 'C') {
    result = acos(a1);
  } else if (symb == 'S') {
    result = asin(a1);
  } else if (symb == 'T') {
    result = atan(a1);
  } else if (symb == 'Q') {
    result = sqrt(a1);
  } else if (symb == 'L') {
    result = log(a1);
  } else if (symb == 'g') {
    result = log10(a1);
  }
  return result;
}

int char_is_number(char c) {
  int res = 0;
  if (((c >= '0' && c <= '9') || (c == '.') || (c == ',') || (c == 'e'))) {
    res = 1;
  }
  return res;
}

void to_number(char *str, double *num) {
  *num = 0;
  *num = atof(str);
}