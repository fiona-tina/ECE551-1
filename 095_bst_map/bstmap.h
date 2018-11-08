#ifndef __BSTMAP_H__
#define __BSTMAP_H__
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>

class BstMap : public Map<K, V>
{
 public:
  class BSTNode
  {
   public:
    BSTNode * left;
    BSTNode * right;
    K key;
    V val;
    BSTNode() : left(NULL), right(NULL){};
    BSTNode(K key, V val) : left(NULL), right(NULL), key(key), val(val){};
  };
  BSTNode * root;

  BstMap() : root(NULL){};
  BstMap(const BstMap & rhs) : root(NULL) { deepcopy(rhs.root); }
  BstMap operator=(const BstMap & rhs) {
    if (this != &rhs) {
      BstMap tmp(rhs);
      std::swap(root, tmp.root);
    }
    return *this;
  }
  void deepcopy(BSTNode * node) {
    if (node) {
      add(node->key, node->val);
      deepcopy(node->left);
      deepcopy(node->right);
    }
  }
  void printhelper(BSTNode * node) {
    if (node == NULL) {
      std::cout << "NULL\n";
    }
    else {
      std::cout << node->key << " " << node->val << std::endl;
      printhelper(node->left);
      printhelper(node->right);
    }
  }
  void printing() { printhelper(root); }
  BSTNode * addhelper(BSTNode * node, const K & key, const V & val) {
    if (node == NULL) {
      BSTNode * newNode = new BSTNode(key, val);
      return newNode;
    }
    else if (key == node->key) {
      node->val = val;
      return node;
    }
    if (key < node->key) {
      node->left = addhelper(node->left, key, val);
    }
    else {
      node->right = addhelper(node->right, key, val);
    }
    return node;
  }
  void add(const K & key, const V & val) { root = addhelper(root, key, val); }

  const V & lookup(const K & key) const throw(std::invalid_argument) {
    BSTNode * dummy = root;
    while (dummy != NULL) {
      if (key < dummy->key) {
        dummy = dummy->left;
      }
      else if (key > dummy->key) {
        dummy = dummy->right;
      }
      else {
        //return dummy->val;
        return dummy->val;
      }
    }

    throw std::invalid_argument("no such key");
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
        root->val = minNodeRight->val;
        root->key = minNodeRight->key;
        root->right = removehelper(root->right, minNodeRight->key);
      }
    }
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

  ~BstMap<K, V>() { recurDestroy(root); }
};
#endif
