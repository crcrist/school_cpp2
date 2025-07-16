/*
 * connor crist
 * intro to CS II
 * 2025-06-30
 * David Stafford
 * Intro Hw
 */

/*  ------------------------------------------------------------------------------
 * Task 1: Create cpp file
 *///  ------------------------------------------------------------------------------

/*---------------------------------------------------------------------------------
 * Task 2: Create a header file
 * Task 3: Place each task into a multi-line comment
 *///--------------------------------------------------------------------------------

/*  ------------------------------------------------------------------------------
* Task 4: Hello World Program
* ------------------------------------------------------------------------------
#include "connor.h"

int main() {
  cout << "hello, connor! \n";
  cout << "intro to comp sci 2 is going to be the best time ever!\n ";
  return 0;
*/
//  ------------------------------------------------------------------------------
/* Task 5: test user input
------------------------------------------------------------------------------
int main() {
  int age = 25;
  int ten_years = 10;
  int sum = age + ten_years;
  cout << connorsnamespace::x << "\n";
  cout << "i am " << age << " years old!\n";
  cout << "if i was 10 years older i would be " << sum << "\n";

  int user_age = 0;
  string name;
  cout << "how old are you? \n";
  cin >> user_age;

  cout << "what is your name? \n";
  cin >> name;
  cout << "hello " << name << ", "
       << "you are " << user_age << " years old! \n";

  return 0;
}
*/

//  ------------------------------------------------------------------------------
/* Task 6: create the simple calculator
  ------------------------------------------------------------------------------
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
}
*/
//  ------------------------------------------------------------------------------
/* Task 7: Create a simple function that says something funny
  ------------------------------------------------------------------------------
void connorsFunction(string fname = "vinny") {
  // code that needs to run
  cout << fname << " thinks this is the best time ever fr \n";
}

int main() {

  connorsFunction("connor");
  connorsFunction();

  return 0;
}
 */
//  ------------------------------------------------------------------------------
/* Task 8: Create a for loop based off the class example
------------------------------------------------------------------------------
 * ( i originally included this with the calculator, but parsing it out!

main() {
  int lval, rval;


  cout << "please enter two integers followed by the calculation you want "
          "performed\n";
  cin >> lval;
  cin >> rval;


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
//
------------------------------------------------------------------------------
// Task 9: Complete an If Else statement
//
------------------------------------------------------------------------------
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
 */

/*
  ------------------------------------------------------------------------------
* Task 10: create an array and output the second item
  ------------------------------------------------------------------------------
int main() {

  int numbers[5] = {10, 20, 30, 40, 50};

  cout << "the second item is: " << numbers[1] << endl;

  return 0;
}
*
*/
