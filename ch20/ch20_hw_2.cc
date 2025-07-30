/*
 * connor crist
 * intro to CS II
 * 2025-07-27
 * David Stafford
 */

#include "../connor.h"
// add 10 contacts

int main() {
  map<string, string> phone_book;

  // adding contacts
  phone_book["Alice"] = "555-1234";
  phone_book["Bob"] = "555-5678";
  phone_book["Charlie"] = "555-9012";
  phone_book["Diana"] = "555-3456";
  phone_book["Ethan"] = "555-7890";
  phone_book["Fiona"] = "555-2468";
  phone_book["George"] = "555-1357";
  phone_book["Hannah"] = "555-8024";
  phone_book["Ivan"] = "555-6913";
  phone_book["Julia"] = "555-4792";

  // looking up a contact
  string name = ""; // change this to be dynamic
  cout
      << "Please enter a name for the phone number you would like to look up\n";
  cin >> name;

  if (phone_book.find(name) != phone_book.end()) {
    cout << name << "'s number is " << phone_book[name] << '\n';
  } else {
    cout << name << " is not in the phone book. \n";
  }

  // traversing the map
  cout << "\n All contacts\n";
  for (const auto &entry : phone_book) {
    cout << entry.first << ": " << entry.second << '\n';
  }

  return 0;
}
