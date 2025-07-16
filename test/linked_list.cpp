
#include "connor.h"

struct Link {
  Link(const string &v, Link *p = nullptr, Link *s = nullptr)
      : value{v}, prev{p}, succ{s} {}
  string value;
  Link *prev;
  Link *succ;
};
Link *insert(Link *p, Link *n) {
  if (n == nullptr)
    return p;
  if (p == nullptr)
    return n;
  n->succ = p;
  if (p->prev)
    p->prev->succ = n;
  n->prev = p->prev;
  p->prev = n;
  return n;
}

int main() {
  Link *norse_gods = new Link{"Thor"};
  string norse_value = *norse_gods;
  cout << norse_value;

  norse_gods = insert(norse_gods, new Link{"Odin"});

  norse_gods = insert(norse_gods, new Link{"Freja"});

  return 0;
}
