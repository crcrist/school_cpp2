/*
 * connor crist
 * intro to CS II
 * 2025-06-30
 * David Stafford
 * create header file


#include "connor.h"

int main() {
  cout << "hello, connor! \n";
  cout << "intro to comp sci 2 is going to be the best time ever!\n ";
  return 0;
}
*/

/* creating namespace */
#include "connor.h"

namespace connorsnamespace {
int x = 500;
}

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
