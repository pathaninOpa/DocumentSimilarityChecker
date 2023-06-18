#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <string.h>
#include "document.h"
using namespace std;

string convertToLower(const string& text){
  string result = text;
  transform(result.begin(), result.end(), result.begin(), [](unsigned char c) { 
    return tolower(c);
  });
  return result;
}

string removePunctuation(const string& text) {
  string result = text;
  result.erase(remove_if(result.begin(), result.end(), [](unsigned char c) { return !isalpha(c) && !isspace(c); }), result.end());
  return result;
}

vector<string> tokenize(Document& document, char delimiter = ' '){
  vector<string> tokens;
  istringstream iss(document.getCleanedWords());
  string token;
  int totalTokens = 0;
  while (getline(iss, token, delimiter)) {
    tokens.push_back(token);
    totalTokens += 1;
  }
  document.setTotalTokens(totalTokens);
  return tokens;
}

unordered_set<string> createStopwordSet() {
  ifstream file("bin/src/stopwords.txt");
  string line;
  unordered_set<string> stopwords;
  
  while(getline(file, line)){
    stopwords.insert(line);
  }

  return stopwords;
}

vector<string> removeStopwords(Document& document) {
  static const unordered_set<string> stopwords = createStopwordSet();
  vector<string> result;
  int cleanedTokens = 0;
  for (const auto& token : document.getTokens()) {
    if (stopwords.find(token) == stopwords.end()) {
      result.push_back(token);
      cleanedTokens++;
    }
  }
  document.setTotalTokensCleaned(cleanedTokens);
  document.setCleanedTokens(result);
  return result;
}