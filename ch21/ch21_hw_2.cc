/*
 * connor crist
 * intro to CS II
 * 2025-07-27
 * David Stafford
 */

#include "../connor.h"

// binary search

int main() {

  vector<string> library = {"The Hobbit",
                            "1984",
                            "Brave New World",
                            "Dune",
                            "To Kill a Mockingbird",
                            "The Great Gatsby",
                            "The Lord of the Rings",
                            "The Catcher in the Rye",
                            "The Handmaid's Tale",
                            "The Alchemist"};

  sort(library.begin(), library.end());

  cout << "sorrted library: \n";
  for (const string &title : library) {
    cout << " - " << title << '\n';
  }

  string search_title;
  cout << "\nEnter a book title to search for: ";
  getline(cin, search_title);

  bool found = binary_search(library.begin(), library.end(), search_title);
  if (found)
    cout << '"' << search_title << "\" was found in the library.\n";
  else
    cout << '"' << search_title << "\" was NOT found in the library.\n";

  return 0;
}
