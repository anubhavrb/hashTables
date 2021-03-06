////////////////////////////////////////////////////////////////////////////////
// words.cpp
//
// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
//
// Outline of client code. Adapted from supplied code
// Anubhav Roy Bhattacharya, Collin Epstein, Harry Zhou
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <string>
#include <queue>
#include <iomanip>

using namespace std;

#include "bst.h"
#include "doublehash.h"
#include "linearprobe.h"
#include "quadraticprobe.h"

const int WIDTH = 22; // results table spacing

bool validTableSize(int& n);
bool isInvalidPunct(const char& c);
template<typename T> void printElement(T t);
void printTitle(const string& name, const string& hits,
                const string& actAvgHits, const string& predAvgHits,
                const string& misses, const string& actAvgMisses,
                const string& predAvgMissess,
                const string& actAlpha);
void printRow(const string& name, const int& hits, const float& actAvgHits,
              const float& predAvgHits, const int& misses,
              const float& actAvgMisses, const float& predAvgMisses,
              const float& actAlpha);
bool evaluateWord(const string& word, LinearProbe& linear,
                  QuadraticProbe& quad, DoubleHash& doub);

int main() {

    // Set the random number seed, set the file names, and get the load
    // factor.
    srand48(time(0));
    const string commonWords = "common.txt";
    const string junkWords = "English16.txt";
    double alpha;
    cout << "Load factor? ";
    cin >> alpha;
    assert(alpha > 0 && alpha < 1);

    // Open the files with the common and junk words, and read the number
    // of words in each (in the first line of the file).
    ifstream inc, inj;
    inc.open(commonWords.c_str());
    if (inc.fail()) {
        cerr << "Error: Cannot open " << commonWords << endl;
        exit(1);
    }
    int numCommon;
    inc >> numCommon;

    inj.open(junkWords.c_str());
    if (inj.fail()) {
        cerr << "Error: Cannot open " << junkWords << endl;
        exit(1);
    }
    int numEnglish16;
    inj >> numEnglish16;

    // Make an array for all the words, load it, then shuffle the entries.
    int numStrings = numCommon + numEnglish16;
    string* allStrings = new string[numStrings];

    // Load common words into array
    for (int i = 0; i < numCommon; i++){
        inc >> allStrings[i];
    }
    
    // Load long words into array
    for (int i = 0; i < numEnglish16; i++){
        inj >> allStrings[i + numCommon];
    }
    
    // Shuffle array elements
    for (int i = numStrings - 1; i >= 0; i--) {
        swap(allStrings[i], allStrings[static_cast<int>(drand48() * i)]);
    }

    // Close the file stream objects.
    inc.close();
    inc.clear();
    inj.close();
    inj.clear();

    // Make the hash table objects and then load them with the saved words.
    
    // find allowed table size
    int arrSize = floor(numStrings / alpha);
    while(!validTableSize(arrSize)) arrSize--;
    cout << "Table size M = " << arrSize << endl;
    
    // initialize hash tables
    LinearProbe linear = LinearProbe(arrSize);
    QuadraticProbe quad = QuadraticProbe(arrSize);
    DoubleHash doub = DoubleHash(arrSize);
    
    // fill hash tables
    bool flag = true;
    for (int i = 0; i < numStrings; i++){
        flag = flag && linear.hash(allStrings[i]);
        flag = flag && quad.hash(allStrings[i]);
        flag = flag && doub.hash(allStrings[i]);
        if(!flag){
            cout << "Unable to enter " << allStrings[i] << " into the tables."
                << endl;
            exit(1);
        }
    }

    // Get the text file to analyze.
    string filename;
    cout << "\nEnter name of file with the text to analyze: ";
    cin >> filename;
    ifstream in;
    in.open(filename.c_str());
    if (in.fail()) {
        cout << "Error opening file.\n";
        exit(1);
    }
    cout << "\nLoading " << filename << "...\n";

    // Make the BST object, then process the file to load the tree.
    BST wordtree;
    
    // parse input - read in character by character
    // make all characters lower case, remove punctuation except apostraphes
    // dashes and whitespace indicate new word beginning
    // TODO: deal with dashes and apostraphes
    string line;
    string temp = "";
    while (in >> line) {
        
        // make all characters lower case
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        
        // remove punctuation other than apostraphes (') and dashes (-)
        line.erase(remove_if(line.begin(), line.end(), isInvalidPunct),
                   line.end());
        
        // evaluate words with dashes - split into two words
        for (int i = 0; i < line.length(); i++){
            if (line.at(i) == '-'){
                if(evaluateWord(temp, linear, quad, doub)){
                    wordtree.insert(temp);
                }
                temp = "";
            }
            else{
                temp += line.at(i);
            }
            
        }
        if(evaluateWord(temp, linear, quad, doub)){
            wordtree.insert(temp);
        }
        temp = "";

    }

    // Close the file stream object.
    in.close();
    in.clear();
    cout << "Done.\n";

    // Get the count threshold and call the reporting method on the tree.
    int thresh;
    cout << "\nEnter count threshold: ";
    cin >> thresh;
    cout << "Analyzing the text...\n";
    //cout << wordtree << endl;
    wordtree.report(thresh);

    // Now get the statistics from the hash table and print this report.
    /* Code INCOMPLETE */
    
    cout << "Hash Table Performance Statistics with load factor = "<< alpha <<
    ", text file " << filename << ":" << endl;
    printTitle("Collision Handling", "# of Hits", "Avg. Probes/Hit",
               "Predicted Probes/Hit", "# of Misses", "Avg. Probes/Miss",
               "Predicted Probes/Miss", "Actual Load");
    printRow("Linear Probing", linear.getNumHits(), linear.getAvgOnSuccess(),
             0.5 * (1 + (1 / (1 - alpha))), linear.getNumMisses(),
            linear.getAvgOnFail(), 0.5 * (1 + (1 / pow((1 - alpha), 2))),
             linear.getLoadFactor());
    printRow("Quadratic Probing", quad.getNumHits(), quad.getAvgOnSuccess(),
             NULL, quad.getNumMisses(), quad.getAvgOnFail(), NULL,
             quad.getLoadFactor());
    printRow("Double Hashing", doub.getNumHits(), doub.getAvgOnSuccess(),
             (1 / alpha) * log(1 / (1 - alpha)), doub.getNumMisses(),
             doub.getAvgOnFail(), 1 / (1 - alpha), doub.getLoadFactor());

    delete [] allStrings; // clean up
    
    return 0;
}

// function to calculate table size and choose largest allowed prime size
bool validTableSize(int& n){
    
    // base cases
    if(n == 0 || n == 1) return false;
    if(n % 2 == 0) return false;
    
    for(int i = 3; i < floor(sqrt(n)); i += 2){
        //cout << i <<endl;
        if(n % i == 0) return false;
    }
    // if exiting for loop, n is prime
    
    // true if congruent to 3 mod 4 AND THUS VALID, else false
    return n % 4 == 3;
}

// checks whether a character is invalid for our purposes
// invalid characters = all punctuation except apostraphes (') and dashes (-)
bool isInvalidPunct(const char& c) {
    return ispunct(c) && c != '\'' && c != '-';
    
}

// Function to pretty print a table
template<typename T> void printElement(T t) {
    cout << left << setw(WIDTH) << setfill(' ') << t;
}

// Function to print a table row prettified
void printTitle(const string& name, const string& hits,
                const string& actAvgHits, const string& predAvgHits,
                const string& misses, const string& actAvgMisses,
                const string& predAvgMissess,
                const string& actAlpha) {
    printElement(name);
    printElement(hits);
    printElement(actAvgHits);
    printElement(predAvgHits);
    printElement(misses);
    printElement(actAvgMisses);
    printElement(predAvgMissess);
    printElement(actAlpha);
    cout << endl;
}

// Function to print a table row prettified
void printRow(const string& name, const int& hits, const float& actAvgHits,
              const float& predAvgHits, const int& misses,
              const float& actAvgMisses, const float& predAvgMisses,
              const float& actAlpha){
    printElement(name);
    printElement(hits);
    printElement(actAvgHits);
    printElement(predAvgHits);
    printElement(misses);
    printElement(actAvgMisses);
    printElement(predAvgMisses);
    printElement(actAlpha);
    cout << endl;
}

// tests word against hash tables, adds to tree if not in hash tables
bool evaluateWord(const string& word, LinearProbe& linear,
                  QuadraticProbe& quad, DoubleHash& doub){
    bool linResult = linear.search(word);
    bool quadResult = quad.search(word);
    bool doubResult = doub.search(word);
    return (!linResult && !quadResult && !doubResult);
}
