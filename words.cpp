// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
// Outline of client code
// Anubhav Roy Bhattacharya, Collin Epstein, Harry Zhou

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cassert>
#include <string>

using namespace std;

#include "bst.h"
#include "doublehash.h"
#include "linearprobe.h"
#include "quadraticprobe.h"

bool validTableSize(int n);

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
    /* Rest of code omitted */
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
    
    //for (int i = 0; i < 20; i++) cout << allStrings[i] << endl;


    // Close the file stream objects.
    inc.close();
    inc.clear();
    inj.close();
    inj.clear();

    // Make the hash table objects and then load them with the saved words.
    
    // find allowed table size
    int arrSize = floor(numStrings / alpha);
    while(!validTableSize(arrSize)) arrSize--;
    // Constructor here with arrSize
    LinearProbe linear = LinearProbe(arrSize, alpha);
    QuadraticProbe quad = QuadraticProbe(arrSize, alpha);
    DoubleHash doub = DoubleHash(arrSize, alpha);
    
    for (int i = 0; i < numStrings; i++){
        linear.hash(allStrings[i]);
        quad.hash(allStrings[i]);
        doub.hash(allStrings[i]);
        
        //do the same thing for quad and double
    }
    cout << linear.search("a") << endl;
    cout << linear.search("Davidson") << endl;
    cout << quad.search("a") << endl;
    cout << quad.search("Davidson") << endl;
    cout << doub.search("a") << endl;
    cout << doub.search("Davidson") << endl;
    
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
    /* Code omitted */

    // Close the file stream object.
    in.close();
    in.clear();
    cout << "Done.\n";

    // Get the count threshold and call the reporting method on the tree.
    int thresh;
    cout << "\nEnter count threshold: ";
    cin >> thresh;
    cout << "Analyzing the text...\n";
    wordtree.report(thresh);

    // Now get the statistics from the hash table and print this report.
    /* Code omitted */

    delete [] allStrings;
    return 0;
}

// function for prime testing. used for calculating table size.
bool validTableSize(int n){
    
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
