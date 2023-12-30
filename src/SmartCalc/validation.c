#include "s21_smartcalc.h"

int validation(char *str) {
  int res = OK;
  int len = strlen(str);
  char number_tmp[255] = "";
  int j = 0;
  if (len > 255) {
    res = ERROR;
  } else if ((len == 1) && strchr("0123456789", str[0]) == NULL) {
    res = ERROR;
  } else if (incorrect_brackets(str) || incorrect_fuc(str) ||
             incorrect_signs(str)) {
    res = ERROR;
  }

  for (int i = 0; i < len && res == OK; i++) {
    if (strchr("cstal0123456789(xX", str[0]) == NULL) {
      res = ERROR;
      break;
    }
    while (char_is_number(str[i])) {
      if (str[i] == ',') str[i] = '.';
      number_tmp[j] = str[i];
      j++;
      i++;
    }
    if (!char_is_number(str[i]) && j > 0) {
      res = incorrect_dot(number_tmp);
      memset(&number_tmp, 0, sizeof(number_tmp));
      j = 0;
    }
  }

  return res;
}

int incorrect_dot(char *str) {
  int res = OK;
  int len = strlen(str);
  int dot_count = 0;
  for (int i = 0; i < len && res == OK; i++) {
    if (str[0] == '.' || str[0] == ',') {
      res = ERROR;
    }
    if (str[i] == '.' || str[i] == ',') {
      if ((str[i + 1] >= '0' && str[i + 1] <= '9') &&
          (str[i - 1] >= '0' && str[i - 1] <= '9')) {
        dot_count += 1;
      } else {
        res = ERROR;
      }
    }
  }
  if (dot_count > 1) {
    res = ERROR;
  }
  return res;
}

int incorrect_signs(char *str) {
  int res = OK;
  int len = strlen(str);
  for (int i = 0; i < len && res == OK; i++) {
    if (str[i] == '(' && strchr("*/^m", str[i + 1]) != NULL) {
      res = ERROR;
    } else if (str[i] == ')' && strchr("0123456789xX", str[i - 1]) == NULL) {
      res = ERROR;
    } else if ((strchr("*/+-", str[i]) != NULL) &&
               ((strchr("*/+-", str[i + 1]) != NULL) ||
                (strchr("*/+-^mnt", str[i - 1]) != NULL))) {
      res = ERROR;
    } else if ((strchr("0123456789xX", str[i]) != NULL && str[i + 1] == '(')) {
      res = ERROR;
    } else if ((str[i] >= '0' && str[i] <= '9') &&
               (str[i + 1] == 'x' || str[i + 1] == 'X' || str[i - 1] == 'x' ||
                str[i - 1] == 'X')) {
      res = ERROR;
    }
  }
  return res;
}

int incorrect_brackets(char *str) {
  int res = OK;
  int count_bracket = 0;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == '(') {
      count_bracket += 1;
    }
    if (str[i] == ')') {
      count_bracket -= 1;
    }
    if ((str[i] == '(') && (str[i + 1] == ')')) {
      count_bracket -= 100;
    }
  }
  if (count_bracket == 0) {
    res = OK;
  } else {
    res = ERROR;
  }
  return res;
}

int incorrect_fuc(char *str) {
  int res = OK;
  int len = strlen(str);
  for (int i = 0; i < len; i++) {
    if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' &&
        str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
               str[i + 3] == 's' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 'l' && str[i + 1] == 'n' && str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 3] == 'd' &&
               (strchr("0123456789 -", str[i + 3]) != NULL)) {
      i += 2;
    } else if ((strchr("+-*/^() xX", str[i]) == NULL) &&
               !char_is_number(str[i])) {
      res = ERROR;
    }
  }
  return res;
}