#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <assert.h>

using namespace std;

struct BSTNode {
  int key;
  int size;
  BSTNode *left;
  BSTNode *right;
  BSTNode (int k) { key = k; size = 1; left = right = NULL; }
};

void fix_size(BSTNode *T)
{
  T->size = 1;
  if (T->left) T->size += T->left->size;
  if (T->right) T->size += T->right->size;
}

// prints out the inorder traversal of T (i.e., the contents of T in sorted order)
void print_inorder(BSTNode *T)
{
  if (T == NULL) return;
  print_inorder(T->left);
  cout << T->key << "\n";
  print_inorder(T->right);
}

// return a pointer to the node with key k in tree T, or NULL if it doesn't exist
BSTNode *find(BSTNode *T, int k)
{
  if (T == NULL) return NULL;
  if (k == T->key) return T;
  if (k < T->key) return find(T->left, k);
  else return find(T->right, k);
}

// return pointer to node of rank r (with r'th largest key; e.g. r=0 is the minimum)
BSTNode *select(BSTNode *T, int r)
{
  assert(T!=NULL && r>=0 && r<T->size);

  int rank_of_root = T->left ? T->left->size : 0;
  if (r == rank_of_root) return T;
  if (r < rank_of_root) return select(T->left, r);
  else return select(T->right, r - rank_of_root - 1);
}

// Join trees L and R (with L containing keys all <= the keys in R)
// Return a pointer to the joined tree.
BSTNode *join(BSTNode *L, BSTNode *R)
{
  // choose either the root of L or the root of R to be the root of the joined tree
  // (where we choose with probabilities proportional to the sizes of L and R)
  if (L == NULL) return R;
  if (R == NULL) return L;
  int random = rand() % (L->size + R->size);
  if (random < L->size) {
    // L stays root
    L->right = join(L->right, R);
    fix_size(L);
    return L;
  } else {
    // R stays root
    R->left = join(L, R->left);
    fix_size(R);
    return R;
  }
}

// remove key k from T, returning a pointer to the resulting tree.
// it is required that k be present in T
BSTNode *remove(BSTNode *T, int k)
{
  assert(T != NULL);
  if (k == T->key) {
    BSTNode *to_delete = T;
    T = join(T->left, T->right);
    delete to_delete;
    return T;
  }
  if (k < T->key) T->left = remove(T->left, k);
  else T->right = remove(T->right, k);
  fix_size(T);
  return T;
}

// Split tree T on key k into tree L (containing keys <= k) and a tree R (containing keys > k)
void split(BSTNode *T, int k, BSTNode **L, BSTNode **R)
{
  if (T == NULL) {
    *L = NULL;
    *R = NULL;
    return;
  }
  if (k < T->key) {
    // recursively split left subtree
    split(T->left, k, L, &T->left);
    *R = T;
  } else {
    split(T->right, k, &T->right, R);
    *L = T;
  }
  fix_size(T);
}

// insert key k into the tree T, returning a pointer to the resulting tree
BSTNode *insert(BSTNode *T, int k)
{
  // If k is the Nth node inserted into T, then:
  // with probability 1/N, insert k at the root of T
  // otherwise, insert k recursively left or right of the root of T
  if (T == NULL) return new BSTNode(k);
  if (rand() % (T->size + 1) == 0) {
    // insert at root
    BSTNode *new_root = new BSTNode(k);
    split(T, k, &new_root->left, &new_root->right);
    fix_size(new_root);
    return new_root;
  }
  if (k < T->key) T->left = insert(T->left, k);
  else T->right = insert(T->right, k);
  fix_size(T);
  return T;
}

#endif
