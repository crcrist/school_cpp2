/*
 * connor crist
 * intro to CS II
 * 2025-06-30
 * David Stafford
 * using pointers with a vector
 */

#include "connor.h"

class RiverList {
private:
  vector<string> *names; // pointer to the vector
public:
  // constructor to allocate the vector
  RiverList() {
    cout << "Constructor for allocating river list \n";
    names = new vector<string>({"Mississippi", "Arkansas", "Hudson", "Colorado",
                                "Nile", "Amazon", "Yangtze", "Yenisei", "Congo",
                                "Yellow"});
  }
  ~RiverList() {
    cout << "Now we delete info with destructor \n";
    delete names;
    names = nullptr;
  }
  // create a function to display the names of our rivers using a pointer
  void showRivers() const {
    if (names != nullptr) {
      cout << "Rivers in list: \n";
      for (const string &rivers : *names) {
        cout << " - " << rivers << '\n';
      }
    } else {
      cout << "Error in the list pointer.";
    }
  }
};

int main() {
  RiverList *list = nullptr; // start with the null

  cout << "Create RiversList object..\n";
  list = new RiverList(); // allocate dynamically

  list->showRivers(); // use the object via the pointer

  cout << "Deleting the list of Rivers: \n";
  delete list;    // manually delete (or calls the destructor)
  list = nullptr; // pointer reset

  if (list == nullptr) {
    cout << "Pointer is now null! \n";
  }
}
