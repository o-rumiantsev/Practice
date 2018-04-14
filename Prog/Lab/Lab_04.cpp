#include <iostream>
#include <string>
#include "structs.h"
#define is_operator(c) (c == '+' || c == '-' || c == '/' || c == '*')
#define has_first_priority(o) (o == "*" || o == "/")
#define has_second_priority(o) (o == "+" || o == "-")

using namespace std;


string *split_by_operators(string line, int *split_length) {
  int operators = 0;
  int length = line.length();
  for (int c = 0; c < length; ++c) {
    if (is_operator(line[c])) ++operators;
  }

  string *expr = new string[2 * operators + 1];
  int index = 0;
  int last_operator = 0;

  if (is_operator(line[0]) && line.length() == 1) {
    expr[index++] = line.substr(0);
    *split_length = index;
    return expr;
  }

  for (int i = 0; i < length; ++i) {
    if (is_operator(line[i])) {
      int diff = i - last_operator;

      if (diff == 0) {
        expr[index++] = line.substr(i, 1);
        last_operator = i + 1;
      } else {
        expr[index++] = line.substr(last_operator, diff);
        expr[index++] = line.substr(i, 1);
        last_operator = i + 1;
      }
    }
  }

  string last = line.substr(last_operator);
  if (last.length() > 0) expr[index++] = last;
  *split_length = index;
  return expr;
}

string *parse_to_string(int argc, char **argv) {
  string *argv_str = new string[argc];

  for (int i = 0; i < argc; ++i) {
    argv_str[i] = argv[i];
  }
  return argv_str;
}

int count_operators(int argc, string *argv_str) {
  int count = 0;

  for (int i = 1; i < argc; ++i) {
    int length = argv_str[i].length();
    for (int j = 0; j < length; ++j) {
      if (is_operator(argv_str[i][j])) ++count;
    }
  }

  return count;
}

string *get_expression(int argc, char **argv, int *expr_length) {
  string *argv_str = parse_to_string(argc, argv);
  int operators = count_operators(argc, argv_str);
  string *expr = new string[2 * operators + 1];
  int index = 0;

  for (int i = 1; i < argc; ++i) {
    int length;
    string *split = split_by_operators(argv_str[i], &length);

    for (int k = index; k < index + length; ++k) {
      expr[k] = split[k - index];
    }

    index += length;
  }

  *expr_length = index;

  return expr;
}

int eval(string op, int a, int b) {
  if (op == "+") return a + b;
  else if (op == "-") return a - b;
  else if (op == "*") return a * b;
  else return a / b;
}

int evaluate(string *expression, int length) {
  deque expr;
  deque params;
  deque operators;

  for (int i = 0; i < length; ++i) {
    expr.push(expression[i]);
  }

  while (expr.length()) {
    string cur = expr.shift();

    if (has_first_priority(cur)) {
      if (!operators.length()) {
        operators.push(cur);
        continue;
      }

      string prev_op = operators.pop();

      if (params.length() >= 2 && has_first_priority(prev_op)) {
        string par2 = params.pop();
        string par1 = params.pop();
        int res = eval(prev_op, stoi(par1), stoi(par2));
        params.push(to_string(res));
        operators.push(cur);
      } else {
        operators.push(prev_op);
        operators.push(cur);
      }
    } else if (has_second_priority(cur)) {
      if (!operators.length()) {
        operators.push(cur);
        continue;
      }

      string prev_op = operators.pop();

      if ((params.length() >= 2 && has_first_priority(prev_op)) ||
        (params.length() >= 2 && has_second_priority(prev_op))) {
        string par2 = params.pop();
        string par1 = params.pop();
        int res = eval(prev_op, stoi(par1), stoi(par2));
        params.push(to_string(res));
        operators.push(cur);
      } else {
        operators.push(prev_op);
        operators.push(cur);
      }
    } else {
      params.push(cur);
    }
  }

  while (operators.length() != 0) {
    string op = operators.pop();
    string par2 = params.pop();
    string par1 = params.pop();
    int res = eval(op, stoi(par1), stoi(par2));
    params.push(to_string(res));
  }

  int result = stoi(params.pop());
  return result;
}

int main(int argc, char **argv) {
  // string str ("+1");
  // int len;
  // string *split = split_by_operators(str, &len);
  // for (int i = 0; i < len; ++i) cout << "|" << split[i] << "|";
  // cout << endl;

  int expr_length;
  string *expression = get_expression(argc, argv, &expr_length);
  int result = evaluate(expression, expr_length);
  cout << result << endl;
}
