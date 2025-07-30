/*
 * connor crist
 * intro to CS II
 * 2025-07-27
 * David Stafford
 */

#include "../connor.h"
// add 10 contacts

template <typename Iterator, typename T>
Iterator my_find(Iterator first, Iterator last, const T &val) {
  while (first != last && *first != val)
    ++first;
  return first;
}

int main() {
  vector<string> books = {"The Hobbit",
                          "1984",
                          "Brave New World",
                          "Dune",
                          "To Kill a Mockingbird",
                          "The Great Gatsby",
                          "The Lord of the Rings",
                          "The Catcher in the Rye",
                          "The Handmaid's Tale",
                          "The Alchemist"};

  // show available books
  cout << "Available books in the library:\n";
  for (const string &book : books) {
    cout << " - " << book << '\n';
  }

  // get user input
  string target;
  cout << "\nEnter the title of the book you want to find: ";
  getline(cin, target); // allows multi-word book titles

  // search for the book
  auto it = my_find(books.begin(), books.end(), target);

  // show result
  if (it != books.end())
    cout << "\n Found: " << *it << '\n';
  else
    cout << "\n Book not found.\n";

  return 0;
}
