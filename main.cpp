#include <bits/stdc++.h>

using namespace std;

string operations = "+-x/";

struct node {
  string value;
  node *left;
  node *right;

  node(string val) : value(val), left(nullptr), right(nullptr) {}
};

float evaluate(node *current) {
  if (!current)
    return 0;

  if (!current->left && !current->right) {
    return stof(current->value);
  }

  float left = evaluate(current->left);
  float right = evaluate(current->right);

  if (current->value == "+")
    return left + right;
  if (current->value == "-")
    return left - right;
  if (current->value == "x")
    return left * right;
  if (current->value == "/") {
    return left / right;
  }

  exit(0);
}

int main(int argc, char *argv[]) {
  stack<node *> stack;

  for (int i = 1; i < argc; i++) {
    string current(argv[i]);
    bool is_operator =
        (current.length() == 1 && operations.find(current) != string::npos);

    if (is_operator) {
      if (stack.size() < 2) {
        return 0;
      }
      node *right = stack.top();
      stack.pop();
      node *left = stack.top();
      stack.pop();

      node *operator_node = new node(current);
      operator_node->left = left;
      operator_node->right = right;

      stack.push(operator_node);
    } else {
      stof(current);
      stack.push(new node(current));
    }
  }

  if (stack.size() != 1) {
    return 1;
  }

  cout << "result: " << evaluate(stack.top()) << endl;

  return 0;
}
