/*
 * connor crist
 * intro to CS II
 * 2025-07-08
 * David Stafford
 * pointer arithmetic - array of 15 elements
 */
#include "../connor.h"

int main() {
  // create array
  string names[] = {"bald eagle", "cardinal",    "robin",   "blue jay",
                    "falcon",     "owl",         "hawk",    "duck",
                    "dove",       "hummingbird", "crane",   "woodpecker",
                    "goose",      "bluebird",    "flamingo"};
  int size = sizeof(names) / sizeof(names[0]);

  // step 2 : define the point to search at the beginning of the array
  string *ptr = names;

  cout << "accessing the array using pointer arithmetic \n";

  for (int i = 0; i < size; ++i) {
    cout << "Name " << i + 1 << " " << *(ptr + i) << endl;
  }

  cout << "accessing names as an array \n";

  for (int i = 0; i < size; ++i) {
    cout << "Name " << i + 1 << " " << ptr[i] << endl;
  }

  return 0;
}
