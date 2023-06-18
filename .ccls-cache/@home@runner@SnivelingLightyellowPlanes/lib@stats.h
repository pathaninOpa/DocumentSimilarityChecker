#include <iostream>
#include <cmath>
#include <unordered_map>
#include <vector>
#include <sstream>
using namespace std;

typedef unordered_map<string, int> TermFrequency;
typedef unordered_map<string, double> TFIDFWeights;

TFIDFWeights calculateTFIDFWeights(const TermFrequency& termFreq, const std::vector<TermFrequency>& allDocs) {
  TFIDFWeights tfidfWeights;
  
  std::unordered_map<std::string, int> documentFreq;
  for (const auto& doc : allDocs) {
    for (const auto& entry : doc) {
      const std::string& term = entry.first;
      documentFreq[term]++;
    }
  }

  for (const auto& entry : termFreq) {
    const std::string& term = entry.first;
    int termFrequency = entry.second;
    int df = documentFreq[term];
    

    double idf = std::log(static_cast<double>(allDocs.size()) / (df + 1));
    
    double tfidf = termFrequency * idf;
    
    tfidfWeights[term] = tfidf;
  }
  
  return tfidfWeights;
}

double calculateDotProduct(const TFIDFWeights&vectorA, const TFIDFWeights& vectorB) {
  double dotProduct = 0.0;
  
  for (const auto& entry : vectorA) {
    const string& term = entry.first;
    int frequencyA = entry.second;
    
    if (vectorB.count(term) > 0) {
      int frequencyB = vectorB.at(term);
      dotProduct += frequencyA * frequencyB;
    }
  }
  
  return dotProduct;
}

double calculateNorm(const TFIDFWeights& vector) {
  double norm = 0.0;
  
  for (const auto& entry : vector) {
    int frequency = entry.second;
    norm += frequency * frequency;
  }
  
  return sqrt(norm);
}

double calculateCosineSimilarity(const TFIDFWeights& vectorA, const TFIDFWeights& vectorB) {
  double dotProduct = calculateDotProduct(vectorA, vectorB);
  double normA = calculateNorm(vectorA);
  double normB = calculateNorm(vectorB);
  
  double similarity = dotProduct / (normA * normB);
  return similarity;
}