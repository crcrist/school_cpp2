/*
 * connor crist
 * intro to CS II
 * 2025-07-27
 * David Stafford
 */

#include "../connor.h"
// put in a text of over 500 words and run the program

int main() {

  map<string, int> words;
  for (string s; cin >> s;)
    ++words[s];

  for (const pair<const string, int> &p : words)
    cout << p.first << ": " << p.second << '\n';

  return 0;
}
