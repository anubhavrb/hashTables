////////////////////////////////////////////////////////////////////////////////
// bst.cpp
//
// Binary search tree class: header file
// CSC 321 Fall 2017 M. Mossinghoff
//
// Implementation file for binary search tree class used to store and count
// relevant words from text files. Adapted from supplied code.
// Anubhav Roy Bhattacharya, Harry Zhou, Collin Epstein
// 10/16/17
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <cstddef>
#include <cstdlib>
using namespace std;
#include "bst.h"

BST::~BST() {
    // Call a private function to delete the entire tree.
    if (root) kill(root);
}

// Function to compare two TNodes, first by count, then by word
// MAYBE DOESN'T WORK MAYBE
int BST::TNode::compareTo(const TNode* other) {
    int dif = this->count - other->count;
    if(dif == 0){
        dif = -1*this->word.compare(other->word);
    }
    
    return dif;
}

void BST::insert(const string& w) {
    // Call a private function to do the insertion, starting at the root.
    insert(root, w);
}

void BST::insert(TNode*& p, const string& w) {
    if (p == NULL) {
        // The node is not in the tree: make a new node.
        p = new TNode(w);
    } else if (w == p->word) {
        // The node is in the tree already: increment its counter.
        p->count++;
    } else if (w < p->word) {
        // Given w is too small, so search the left subtree.
        insert(p->left, w);
    } else {  // w > p->word
        // Given w is too big, so search the right subtree.
        insert(p->right, w);
    }
}

int BST::remove(const string& w) {
    return remove(w, root);
}

int BST::remove(const string& w, TNode*& p) {
    // If there is nothing in the subtree, the element is not in the tree.
    if (p == NULL) return 0;
    if (w < p->word) return remove(w, p->left);
    if (w > p->word) return remove(w, p->right);
    // At this point, we know that w equals p->word.
    TNode* q = p;
    if (p->right == NULL) {
        // Either p is a leaf, or p has a left child but no right child.
        p = p->left;
    } else if (p->left == NULL) {
        // p has a right child but no left child.
        p = p->right;
    } else {
        // p has both a left and a right child.  Use improved "copy"
        // strategy.
        // Delete the node that p points to and replace it in the tree
        // with the successor node.
        p = removeSmallest(p->right);
        p->left = q->left;
        p->right = q->right;		
    }
    int ans = q->count;
    delete q;
    return ans;
}

// Return the address of the node with the smallest key in the tree pointed
// to by p, and remove this node from the tree.
BST::TNode* BST::removeSmallest(TNode*& p) {
    // Go left while there is a smaller element in the tree.
    if (p->left) return removeSmallest(p->left);
    // No left child, so there is no smaller element in the tree.
    TNode* ans = p;
    p = p->right;    // Required since p is a reference.
    return ans;
}

// Public counting function.
int BST::count(int t) const {
    // Call a private function to do the count, starting at the root
    // pointer.
    // Counts only nodes with count value >= t.
    return count(t, root);
}

// Auxilliary private counting function.
int BST::count(int t, TNode* p) const {
    if (p) {
        int sum = (p->count >= t) ? 1 : 0; // Count the current node first.
        sum += count(t, p->left);          // Count nodes in the left subtree.
        sum += count(t, p->right);         // Count nodes in the right subtree.
        return sum;
    }
    return 0;  // When p is null.
}

// Postorder traversal
void BST::kill(TNode* p) {
    if (p->left) kill(p->left);          // Delete nodes in the left subtree.
    if (p->right) kill(p->right);        // Delete nodes in the right subtree.
    delete p;                            // Delete current node.
}

// Inorder traversal
void BST::print(ostream& out, TNode* p) const {
    if (p->left) print(out, p->left);          // Print smaller words
    out << p->word << " " << p->count << endl; // Print current word
    if (p->right) print(out, p->right);        // Print larger words
}

// Friend output operator.
ostream& operator<<(ostream& out, const BST& wt) {
    // Call a private function to do the printing, starting at the root.
    if (wt.root) wt.print(out, wt.root);
    return out;
}

void BST::report(int t) const {
    if (root) {
        int num = count(t);
        TNode** a = new TNode*[num];
        int k = 0;
        fill(t, a, k, root);
        sort(a, 0, num-1);
        for (int i=0; i<num; i++) {
            cout << a[i]->word << " " << a[i]->count << endl;
        }
        delete [] a;
    } else {
        cout << "Tree is empty!\n";
    }
}

// Fill the array a with pointers in the subtree rooted at p beginning at
// index k in the array a.
// Precondition: p is not null, and the array has sufficient room.
void BST::fill(int t, TNode** a, int& k, TNode* p) const {
    if (p == NULL) return;
    if (p->count >= t) {
        a[k] = p;
        k++;
    }
    fill(t, a, k, p->left);
    fill(t, a, k, p->right);
}

// Sort the elements of a by the values in the nodes they point to.
// Sort by count, in descending order, and break ties by using alphabetical
// order.  This must be O(n log(n)).
// Using quick sort.
void BST::sort(TNode** a, int first, int last) {
    if (first < last) {
        int q = partition(a, first, last);
        sort(a, first, q - 1);
        sort(a, q + 1, last);
    }
}

// Hoare partitioning in descending order by count
int BST::partition(TNode** a, int first, int last) {
    int i = first, j = last - 1;
    while (i <= j) {
        while (a[i]->compareTo(a[last]) > 0) {
            i++;
        }
        while ((i <= j) && (a[j]->compareTo(a[last])) <= 0) {
            j--;
        }
        
        if (i < j) {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    swap(a[i], a[last]);
    return i;
}
