#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>

#ifndef document_h
#define document_h

using namespace std;

class Document {
    private:
        int totalWords;
        int totalTokensCleaned;
        int totalTokens;
        string path;
        string words;
        string cleanedWords;
        vector<string> tokens;
        vector<string> cleanedTokens;

    public:
        Document(){
          totalWords = 0;
          totalTokensCleaned = 0;
          totalTokens = 0;
        }
        ~Document() {}
        string getCleanedWords(){
          return cleanedWords;
        }
        void setCleanedWords(string cw){
          cleanedWords = cw;
        }
        int getTotalWords() const {
            return totalWords;
        }

        vector<string> getCleanedTokens(){
          return cleanedTokens;
        }

        void setCleanedTokens(vector<string> ct){
            cleanedTokens = ct;
        }
        void setTotalWords(int value) {
            totalWords = value;
        }
    
        int getTotalTokensCleaned() const {
            return totalTokensCleaned;
        }
    
        void setTotalTokensCleaned(int value) {
            totalTokensCleaned = value;
        }
    
        int getTotalTokens() const {
            return totalTokens;
        }
    
        void setTotalTokens(int value) {
            totalTokens = value;
        }
    
        void setTokens(vector<string> t){
          tokens = t;
        }

        vector<string> getTokens(){
          return tokens;
        }

        string& getPath(){
            return path;
        }
    
        void setPath(string filePath) {
            path = filePath;
        }  
    
        void setWords(string w){
          words = w;
        }
    
        string getWords(){
          return words;
        }
};

#endif