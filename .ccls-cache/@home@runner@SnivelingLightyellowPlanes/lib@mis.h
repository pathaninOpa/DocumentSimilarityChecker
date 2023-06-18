#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <filesystem>
#include <dirent.h>
#include <sys/stat.h>
#include "./document.h"
using namespace std;

//Prototypes
void wait(int);
void loadingAnim(float, const char * = "Progress");
void clearConsole();
int alphabetToInt(char);
char intToAlphabet(int);
void saveToCSV(const vector<pair<string, int>>& , const string&);
void displaySort();
void displaySortOptions();
bool isSortChoiceValid(int choice, int range);
bool testSortOptions(char choice, int range);
//

void wait(int ms){
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void loadingAnim(float prog, const char * title) {
    int barWidth = 30;
    cout << title << ": [";
    int pos = barWidth * prog;
    for (int i = 0; i < barWidth; ++i) {
        if (i < pos)
            cout << "=";
        else if (i == pos)
            cout << ">";
        else
            cout << " ";
    }
    cout << "] " << int(prog * 100.0) << "%\r";
    clearConsole();
    cout.flush();
    wait(100);
}

void clearConsole() {
    #ifdef _WIN32
        std::system("cls");
    #else
        std::system("clear");
    #endif
}

int alphabetToInt(char c) {
   return static_cast<int>(c - 'a' + 1);
}

char intToAlphabet(int i ){
   return static_cast<char>('a' - 1 + i);
}

void saveToCSV(const vector<pair<string, int>>& vec, const string& filename) {
    ofstream outputFile(filename);
    int count = vec.size();
    if (!outputFile) {
        cerr << "Error creating the file: " << filename << endl;
        return;
    }

    for (const auto& pair : vec) {
        outputFile << pair.first << "," << pair.second << "\n";
    }

    outputFile.close();
    cout << "Successfully exported to " << filename << endl;
}


void displaySort() {
  string options[] = {"Sort Report by Alphabets", "Sort Report by Frequency", "Exit"};
  for(int i = 0; i < sizeof(options)/sizeof(string); i++) {
    cout << i+1 << ". " << options[i] << endl;
  }
}

void displaySortOptions(){
  string options[] = {"Sort Report in Ascending  Order", "Sort Report in Descending Order", "Back"};
  for(int i = 0; i < sizeof(options)/sizeof(string); i++) {
    cout << "  "<< intToAlphabet(i+1) << ". " << options[i] << endl;
  }
}

bool isSortChoiceValid(int choice, int range) {
    if (choice > range || choice <= 0) {
        clearConsole();
        cout << "Invalid Choice. Please try again." << endl;
        return false;
    }
    return true;
}

bool testSortOptions(char choice, int range){
  int temp = alphabetToInt(choice);
  if(isSortChoiceValid(temp, range)){
    return true;
  }
  return false;
}

void displayResults(Document& documentA, Document& documentB, float sim) {
    cout << "------------------------- Results -------------------------" << endl;
    cout << "Similarity: " << sim * 100 << "%" << endl;

    cout << "----------------------------------------------------------" << endl;
    cout << "File: " << documentA.getPath() << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Total Words:             " << documentA.getTotalWords() << endl;
    cout << "Total Tokens:            " << documentA.getTotalTokens() << endl;
    cout << "Total Cleaned Tokens:    " << documentA.getTotalTokensCleaned() << endl;
    cout << "----------------------------------------------------------" << endl;
  
    cout << "File: " << documentB.getPath() << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "Total Words:             " << documentB.getTotalWords() << endl;
    cout << "Total Tokens:            " << documentB.getTotalTokens() << endl;
    cout << "Total Cleaned Tokens:    " << documentB.getTotalTokensCleaned() << endl;
  cout << "-----------------" << endl;
}

bool isDirectoryEmpty(const string& directoryPath) {
  DIR* dir = opendir(directoryPath.c_str());
  if (dir == nullptr) {
    return false;
  }
  
  struct dirent* ent = readdir(dir);
  while (ent != nullptr) {
    if (strcmp(ent->d_name, ".") != 0 && strcmp(ent->d_name, "..") != 0) {
      closedir(dir);
      return false;
    }
    ent = readdir(dir);
  }
  closedir(dir);
  return true; 
}

void getFilesRecursive(const string& directoryPath, vector<string>& fileNames) {
  DIR* dir = opendir(directoryPath.c_str());
  if (dir == nullptr) {
    return;
  }

  struct dirent* ent = readdir(dir);
  while (ent != nullptr) {
    if (ent->d_type == DT_REG) {
      fileNames.push_back(directoryPath + "/" + ent->d_name);
    } else if (ent->d_type == DT_DIR && string(ent->d_name) != "." && string(ent->d_name) != "..") {
      string subdirectoryPath = directoryPath + "/" + ent->d_name;
      getFilesRecursive(subdirectoryPath, fileNames);
    }
    ent = readdir(dir);
  }

  closedir(dir);
}

vector<string> getAllFilesInDirectory(const string& directoryPath) {
  vector<string> fileNames;
  getFilesRecursive(directoryPath, fileNames);
  return fileNames;
}

int countWords(string str){
    int n = str.size();
    if(n == 0){
        return 0;
    }
    int wordCount = 0;
    bool isWord = false;
    int endOfLine = n - 1;
    for (int i = 0; i < n; i++) {
        if (isalpha(str[i]) && i != endOfLine) {
            isWord = true;
        }
        else if (!isalpha(str[i]) && isWord){
            wordCount++;
            isWord = false;
        }

        else if (isalpha(str[i]) && i == endOfLine) {
            wordCount++;
        }
    }
    return wordCount;
}