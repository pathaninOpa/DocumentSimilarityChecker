#include <cctype>
#include <algorithm>
#include <string.h>
#include <unordered_map>
#include <vector>
#include <iostream>

using namespace std;

vector<pair<string,int>> sortFrequencies(unordered_map<string, int>);
vector<pair<string, int>> convertToVector(unordered_map<string, int>);

vector<pair<string, int>> sortFrequencies(unordered_map<string, int> freq, int choice, char option) {
  vector<pair<string, int>> vec = convertToVector(freq); 
  int n = vec.size();
  switch(choice) {
    case 1:
      switch(option) {
        case 'a':
          sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.first < b.first;
          });
          break;
        case 'b':
          sort(vec.begin(), vec.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
            return a.first > b.first;
          });
          break;
        default:
          break;
      }
      break;
    case 2:
      switch(option) {
        case 'a':
          for(int i = 0; i < n; i++) {
            for(int j = 0; j < n - i - 1; j++) {
              if(vec[j].second < vec[j + 1].second) {
                swap(vec[j], vec[j + 1]);
              }
            }
          }
          break;
        case 'b':
          for(int i = 0; i < n; i++) {
            for(int j = 0; j < n - i - 1; j++) {
              if(vec[j].second > vec[j + 1].second) {
                swap(vec[j], vec[j + 1]);
              }
            }
          }
          break;
        default:
          break;
      }
      break;
    default:
      break;
  }

  return vec;
}


vector<pair<string, int>> convertToVector(unordered_map<string, int> freq) {
  return vector<pair<string, int>>(freq.begin(), freq.end());
}

