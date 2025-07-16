/*
 * connor crist
 * intro to CS II
 * 2025-07-09
 * David Stafford
 * pointer arithmetic - array of 15 elements
 */
#include "../connor.h"

class Composer {
  string name;
  int birthYear;

public:
  // Explicit constructor
  explicit Composer(string n, int y) : name{n}, birthYear{y} {
    cout << "Constructed: " << name << "\n";
  }

  // Copy constructor
  Composer(const Composer &c) : name{c.name}, birthYear{c.birthYear} {
    cout << "Copied: " << name << "\n";
  }
  // Move constructor
  Composer(Composer &&c) noexcept : name{move(c.name)}, birthYear{c.birthYear} {
    cout << "Moved: " << name << "\n";
  }

  // Copy assignment
  Composer &operator=(const Composer &c) {
    if (this != &c) {
      name = c.name;
      birthYear = c.birthYear;
      cout << "Copy-assigned: " << name << "\n";
    }
    return *this;
  }

  // Move assignment
  Composer &operator=(Composer &&c) noexcept {
    if (this != &c) {
      name = move(c.name);
      birthYear = c.birthYear;
      cout << "Move-assigned\n";
    }
    return *this;
  }

  void print() const { cout << name << " (" << birthYear << ")\n"; }
};

int main() {
  // 10 musical composers - reserve space to avoid reallocations
  vector<Composer> composers;
  composers.reserve(10);
  cout << "Initial capacity: " << composers.capacity() << "\n\n";

  // List initialization with explicit constructor
  composers.emplace_back(Composer("Mozart", 1756));
  composers.emplace_back(Composer("Beethoven", 1770));
  composers.emplace_back(Composer("Chopin", 1810));
  composers.emplace_back(Composer("Brahms", 1833));
  composers.emplace_back(Composer("Stravinsky", 1882));
  composers.emplace_back(Composer("Rachmaninoff", 1873));
  composers.emplace_back(Composer("Gershwin", 1898));
  composers.emplace_back(Composer("Vivaldi", 1678));

  cout << "\nCapacity after adding: " << composers.capacity() << "\n\n";

  // Copy constructor
  Composer bach("Bach", 1685);
  composers.push_back(bach);

  // move constructor
  composers.push_back(Composer("Tchaikovsky", 1840));

  // copy assignment
  Composer temp("Debussy", 1862);
  temp = bach;

  // move assignment
  Composer moved("Gershwin", 1898);
  moved = move(temp);

  cout << "\nFinal list:\n";
  for (const auto &c : composers)
    c.print();
}
