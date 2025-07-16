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

void connorsFunction(string fname = "vinny") {
  // code that needs to run
  cout << fname << " thinks this is the best time ever fr \n";
}

int main() {

  connorsFunction("connor");
  connorsFunction();

  return 0;
}
