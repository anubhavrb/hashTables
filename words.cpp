0// CSC 321 Fall 2017 Mossinghoff
// Program 2: Nonundergraduate Zarathustrianism
// Outline of client code
// Your names here!

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

    // Close the file stream objects.
    inc.close();
    inc.clear();
    inj.close();
    inj.clear();

    // Make the hash table objects and then load them with the saved words.
    /* Code omitted */
    /* Code omitted */

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
