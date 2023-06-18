#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include "document.h"

using namespace std;

unordered_map<string, int> getTermFrequencies(Document& document) {
  unordered_map<string, int> frequencies;

  for (const string &token : document.getCleanedTokens()) {
    frequencies[token]++;
  }
  return frequencies;
}