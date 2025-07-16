/*
 * connor crist
 * intro to CS II
 * 2025-06-30
 * David Stafford
 * create calculator
 */

#include "connor.h"

void silly() { cout << "I'm a mathematical genius!\n"; }

int main() {
  int lval, rval, add, subtract, mult;
  float div;

  cout << "please enter two integers followed by the calculation you want "
          "performed\n";
  cin >> lval;
  cin >> rval;

  add = lval + rval;
  subtract = lval - rval;
  mult = lval * rval;
  div = lval / (float)rval;

  cout << endl << "sum = " << add << "\n";
  cout << endl << "difference = " << subtract << "\n";
  cout << endl << "product = " << mult << "\n";
  cout << endl << "quotient = " << div << "\n";

  silly();

  cout << "would you like to take the factorial of your first number?\nplease "
          "enter 'y' for yes or 'n' for no\n";

  int factorial_lval = 1;
  char factorial_prompt;
  cin >> factorial_prompt;

  // keep asking the user until we get a y or n
  while (factorial_prompt != 'Y' && factorial_prompt != 'y' &&
         factorial_prompt != 'N' && factorial_prompt != 'n') {
    cout << "that's not 'y' or 'n', please enter either 'y' or 'n'!\n";
    cin >> factorial_prompt;
  }

  // if y then perform factorial calculation
  if (factorial_prompt == 'y' || factorial_prompt == 'Y') {
    for (int i = 1; i <= lval; i++) {
      factorial_lval *= i;
    }
    cout << "the factorial of " << lval << " is " << factorial_lval << "\n";
  } else if (factorial_prompt == 'n' || factorial_prompt == 'N') {
    cout << "skipping the factorial calculation.\n";
  }

  return 0;
}
