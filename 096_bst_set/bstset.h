#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename K>

class BstSet : public Set<K>
{
 public:
  class BSTNode
  {
   public:
    BSTNode * left;
    BSTNode * right;
    K key;
    BSTNode() : left(NULL), right(NULL){};
    BSTNode(K key) : left(NULL), right(NULL), key(key){};
  };
  BSTNode * root;

  BstSet() : root(NULL){};
  BstSet(const BstSet & rhs) : root(NULL) { deepcopy(rhs.root); }
  BstSet operator=(const BstSet & rhs) {
    if (this != &rhs) {
      BstSet tmp(rhs);
      std::swap(root, tmp.root);
    }
    return *this;
  }
  void deepcopy(BSTNode * node) {
    if (node) {
      add(node->key);
      deepcopy(node->left);
      deepcopy(node->right);
    }
  }
  void printhelper(BSTNode * node) {
    if (node == NULL) {
      std::cout << "NULL\n";
    }
    else {
      std::cout << node->key << std::endl;
      printhelper(node->left);
      printhelper(node->right);
    }
  }
  void printing() { printhelper(root); }
  BSTNode * addhelper(BSTNode * node, const K & key) {
    if (node == NULL) {
      BSTNode * newNode = new BSTNode(key);
      return newNode;
    }
    else if (key == node->key) {
      return node;
    }
    if (key < node->key) {
      node->left = addhelper(node->left, key);
    }
    else {
      node->right = addhelper(node->right, key);
    }
    return node;
  }
  void add(const K & key) { root = addhelper(root, key); }

  bool contains(const K & key) const {
    BSTNode * dummy = root;
    while (dummy != NULL) {
      if (key < dummy->key) {
        dummy = dummy->left;
      }
      else if (key > dummy->key) {
        dummy = dummy->right;
      }
      else {
        return true;
      }
    }

    return false;
  }
  BSTNode * minNode(BSTNode * node) {
    if (!node->left) {
      return node;
    }
    else {
      return minNode(node->left);
    }
  }
  BSTNode * removehelper(BSTNode * root, const K & key) {
    if (!root)
      return root;
    if (root->key > key) {
      root->left = removehelper(root->left, key);
    }
    else if (root->key < key) {
      root->right = removehelper(root->right, key);
    }

    else {
      if (!root->left) {
        BSTNode * right = root->right;
        delete root;
        return right;
      }
      else if (!root->right) {
        BSTNode * left = root->left;
        delete root;
        return left;
      }
      else {
        BSTNode * minNodeRight = minNode(root->right);

        root->key = minNodeRight->key;
        root->right = removehelper(root->right, minNodeRight->key);
      }
    }
    return root;
  }
  void remove(const K & key) {
    //search
    BSTNode * dummy = root;
    root = removehelper(dummy, key);
  };
  void recurDestroy(BSTNode * node) {
    if (node) {
      recurDestroy(node->left);
      recurDestroy(node->right);
      delete node;
    }
  }

  ~BstSet<K>() { recurDestroy(root); }
};
#endif
