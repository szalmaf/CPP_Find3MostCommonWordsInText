//
//  main.cpp
//  C++_Find3MostCommonWordsInText
//
//  Created by Ferenc Szalma on 10/9/16.
//  Copyright © 2016 Ferenc Szalma. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <unordered_map>
using namespace std;

bool fnctn(int lhs, int rhs) {
    return lhs > rhs;
}

auto createWordMap(istream& inStream) {
    // Create map in "dict" of how many times each word appears
    unordered_map<string, int> dict;
    typedef istream_iterator<string> iIter;
    for_each(iIter(inStream), iIter(),
             [&dict] (string word) { ++dict[word]; });
    return dict;
}

auto createFrequencyMap(const unordered_map<string, int>& dict) {
    // Find top 3 most used words
    auto fn1 = [](auto lhs, auto rhs){ return lhs > rhs; }; // Lambda fn is allowed to be defined using auto in C++14
    //    bool(*fn)(int,int) = [](int lhs, int rhs){ return lhs > rhs; }; // C++11 type fn lambda function definition
    //    bool (*fn2)(int,int) = fnctn; // C++98 style fn definition
    multimap<int, string, bool(*)(int,int)> top3(fn1); // Ordered multimap from hi to lo
    auto insertReversePair = [&top3](auto pair){ top3.insert(make_pair(pair.second, pair.first)); };
    for_each(dict.begin(), dict.end(), insertReversePair); // Lambda fn passed to a generic algorithm
    return top3;
}

void printTopN(multimap<int, string, bool(*)(int,int)>::iterator top3It, const int n) {
    // Assuming there are at least 3 top words, they are:
    cout << "Three most used words: ";
    for(int i = 0; i < n; ++i)
        cout << "\"" << top3It++->second << "\", ";
    cout << "\"" << top3It->second << "\"." << endl;
}

int main(int argc, const char * argv[]) {
    
    ifstream inputFile;
    inputFile.open("/Users/szalmaf/Data/example_text.txt");
    inputFile.close();
    
    auto dict = createWordMap(inputFile);
    
    auto topN = createFrequencyMap(dict);

    printTopN(topN.begin(), 10);
    
    
    
    return 0;
}
