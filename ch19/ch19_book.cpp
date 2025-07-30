/*
 * connor crist
 * intro to CS II
 * 2025-07-23
 * David Stafford
 * create a program illustrating storing data into vector, show list operations
 * in sequence and iterators, container traversal for insert and erase functions
 * using former us presidents
 */

#include "../connor.h"

int main() {

  int initializer[7] = {1, 2, 3, 4, 5, 6, 7};
  int *first = initializer;
  int *last = initializer + 7;

  // compare using vector
  {
    vector<int> v(first, last);
    vector<int>::iterator p = v.begin(); // take a vector
    ++p;
    ++p;
    ++p; // point to its 4th element (index 3)
    vector<int>::iterator q = p;
    ++q; // point to its 5th element (index 4)

    p = v.insert(p, 99);
    p = v.erase(p);

    cout << "vector after insert and erase:\n";
    for (int x : v)
      cout << x << ' ';
    cout << "\n";
  }

  // compare using list
  {
    list<int> v(first, last);
    list<int>::iterator p = v.begin();
    ++p;
    ++p;
    ++p;
    list<int>::iterator q = p;
    ++q;

    p = v.insert(p, 88);
    p = v.erase(p);

    cout << "list after insert and erase:\n";
    for (int x : v)
      cout << x << ' ';
    cout << "\n";
  }

  return 0;
}
