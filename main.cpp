#include <iostream>
#include <fstream>
#include "./lib/term_freq.h"
#include "./lib/preprocess.h"
#include "./lib/stats.h"
#include "./lib/sorting.h"
#include "./lib/mis.h"
#include "./lib/document.h"

using namespace std;

typedef unordered_map<string, double> TFIDFWeights;
const string& dir = "./bin/origin";
void task(int, char, vector<int>);

int main() {
    while(true){
    vector<int> selectedFilesIndice;
      int choice;
      vector<string> allFiles = getAllFilesInDirectory(dir);
      if(isDirectoryEmpty(dir) || allFiles.size() < 2){
        cout << "It seems you have not imported at least two document files. This program requires two files to check for their similarity. Please import them to the directory /bin/origin before proceeding." << endl;
        exit(1);
      }else{
        if(allFiles.size() > 2){
          cout << "<Selection Menu>" << endl;
          int i = 0;
          for(auto& file: allFiles){
            i++;
            cout << i << ". " << file.substr(file.find_last_of('/')) << endl;
          }
          int numSelected = 0;
          while(numSelected < 2){
            int selected;
            cout << static_cast<char>('A' + numSelected) << ">> ";
            cin >> selected;
            if(selected > i || selected <= 0){
              cout << "Invalid File Index. Try Again." << endl;
            }else{
              selectedFilesIndice.push_back(selected-1);
              numSelected += 1;
            }
          }
        }else{
          selectedFilesIndice.push_back(0);
          selectedFilesIndice.push_back(1);
        }
      }
      
      displaySort();
      cout << ">> ";
      cin >> choice;
      
      if(isSortChoiceValid(choice, 3)){
        if(choice == 3){
          exit(0);
        }
        displaySortOptions();
        char option;
        cout << ">> ";
        cin >> option;
        if(testSortOptions(option, 3)){
          if(!(option == 'c')){
            task(choice, option, selectedFilesIndice);
          }else{
            clearConsole();
          }
        }
      }else{
        clearConsole();
      }
    }
    
    return 0;
}

void task(int c1, char c2, vector<int> selectedFilesIndices){
  vector<string> allFiles = getAllFilesInDirectory(dir);
  ifstream origin_file;
  ifstream test_file;
  string line, origin_str;
  string lineTest, test_str;
  float progress = 0;
  origin_file.open(allFiles.at(selectedFilesIndices.at(0)));
  test_file.open(allFiles.at(selectedFilesIndices.at(1)));

  Document* docA = new Document();
  Document* docB = new Document();
  
  docA->setPath(allFiles.at(selectedFilesIndices.at(0)));
  docB->setPath(allFiles.at(selectedFilesIndices.at(1)));
  
  while(getline(origin_file, line)){
    origin_str += line;
  }
  
  progress += 0.1;
  loadingAnim(progress);
  
  while(getline(test_file, lineTest)){
    test_str += lineTest;
  }
  
  docA->setWords(origin_str);
  docB->setWords(test_str);
  docA->setTotalWords(countWords(docA->getWords()));
  docB->setTotalWords(countWords(docB->getWords()));
  progress += 0.1;
  loadingAnim(progress);
  test_file.close();
  origin_file.close();

  string preprocessedTextA = removePunctuation(convertToLower(docA->getWords()));
  docA->setCleanedWords(preprocessedTextA);
  vector<string> tokensA = tokenize(*docA);
  docA->setTokens(tokensA);
  vector<string> cleanedTokensA = removeStopwords(*docA);
  unordered_map<string, int> frequenciesA = getTermFrequencies(*docA);
  progress += 0.2;
  loadingAnim(progress);
  
  string preprocessedTextB = removePunctuation(convertToLower(docB->getWords()));
  docB->setCleanedWords(preprocessedTextB);
  vector<string> tokensB = tokenize(*docB);
  docB->setTokens(tokensB);
  vector<string> cleanedTokensB = removeStopwords(*docB);
  unordered_map<string, int> frequenciesB = getTermFrequencies(*docB);
  vector<TermFrequency> docs;
  progress += 0.2;
  loadingAnim(progress);
  
  docs.push_back(frequenciesA);
  docs.push_back(frequenciesB);
  TFIDFWeights weightA = calculateTFIDFWeights(frequenciesA, docs);
  TFIDFWeights weightB = calculateTFIDFWeights(frequenciesB, docs);
  progress += 0.2;
  loadingAnim(progress);
  
  double sim = calculateCosineSimilarity(weightA, weightB);
  progress += 0.1;
  loadingAnim(progress);
  
  vector<pair<string,int>>sortedA = sortFrequencies(frequenciesA, c1, c2);
  vector<pair<string,int>>sortedB = sortFrequencies(frequenciesB, c1, c2);
  
  progress += 0.1;
  loadingAnim(progress);
  clearConsole();
  cout << "Export Results? [Y/n]: ";
  char in;
  cin >> in;
  clearConsole();
  displayResults(*docA, *docB, sim);
  if(in == 'y' || in == 'Y'){
    saveToCSV(sortedA, "./bin/export/A.csv");
    saveToCSV(sortedB, "./bin/export/B.csv");
  }
  cout << "------" << endl;
}