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

void print_vector(const vector<string> &v) {
  cout << "vector contents: \n";
  for (const auto &name : v)
    cout << " - " << name << "\n";
}

void print_list(const list<string> &l) {
  cout << "list contents: \n";
  for (const auto &name : l)
    cout << " - " << name << "\n";
}

int main() {
  // sample data: former us presidents
  vector<string> presidents = {"George Washington",     "Thomas Jefferson",
                               "Abraham Lincoln",       "Theodore Roosevelt",
                               "Franklin D. Roosevelt", "Andrew Jackson",
                               "James Garfield",        "Zachary Taylor",
                               "James Monroe",          "James Polk"};

  // vector operations
  cout << "=== VECTOR DEMONSTRATION ===\n";
  vector<string>::iterator vit = presidents.begin();
  ++vit; // move to 2nd element ("Thomas Jefferson")

  // insert a president before the 2nd element
  vit = presidents.insert(vit, "John Adams");

  // erase the newly inserted element
  vit = presidents.erase(vit); // vit now points to "Thomas Jefferson"

  // traverse and print
  print_vector(presidents);

  // list operations
  cout << "\n=== LIST DEMONSTRATION ===\n";
  list<string> pres_list(presidents.begin(), presidents.end());
  list<string>::iterator lit = pres_list.begin();
  advance(lit, 2); // move to 3rd element

  // insert into list
  lit = pres_list.insert(lit, "James Madison");

  // erase that same element
  lit = pres_list.erase(lit);

  // traveerse and print
  print_list(pres_list);

  return 0;
};
