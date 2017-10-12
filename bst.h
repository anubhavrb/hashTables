// Binary search tree class: header file
// CSC 321 Fall 2017
// M. Mossinghoff

#ifndef bst_h
#define bst_h
#include <cstddef>
#include <string>

class BST {
  public:
    BST() : root(NULL) {}
    ~BST();

    // Insert the item in the tree if it is not already there; increment
    // the item's counter if it is already there.
    void insert(const string&);

    // Count the number of nodes currently in the tree, whose count is
    // greater than or equal to the supplied argument, if it is present.
    // If the argument is absent, it returns the number of nodes in the
    // tree.
    int count(int=1) const;

    // Remove the item from the tree if it is there and return the value of
    // the counter stored with the item.  If the item is not there, return 0.
    int remove(const string&);

    // Print all the words in order by count then alphabetically.
    void report(int) const;

    // Print the items and counts stored in the tree in order.
    friend ostream& operator << (ostream&, const BST&);

  private:

    class TNode {
      public:
        string word;
        int count;
        TNode* left;
        TNode* right;
        TNode(const string& w) : word(w), count(1), left(0), right(0) {}
    };

    TNode* root;

    // Private member functions implementing recursive traversals or searches.
    void insert(TNode*&, const string&);
    int remove(const string&, TNode*&);
    TNode* removeSmallest(TNode*&);
    int count(int, TNode*) const;
    void kill(TNode*);
    void print(ostream&, TNode*) const;
    int fill(int, TNode**, int, TNode*) const;

    // Static auxilliary methods.
    static void sort(TNode**, int, int);

    // Disable copy constructor and assignment operator.
    BST(const BST&);
    BST& operator=(const BST&);
};

#endif
