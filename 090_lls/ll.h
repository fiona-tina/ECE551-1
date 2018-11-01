#ifndef _LL_H_
#define _LL_H_
#include <assert.h>

#include <cstdlib>
#include <exception>
#include <iostream>
//YOUR CODE GOES HERE

template<typename T>
class LinkedList
{
 private:
  class Node
  {
   public:
    T data;
    Node * next;
    Node * prev;
    //Node(const T& a): data(a), next(NULL), prev(NULL) {}
    Node() : next(NULL), prev(NULL){};
    Node(const T & a, Node * n, Node * p) : data(a), next(n), prev(p){};
  };
  int size;
  Node * head;
  Node * tail;

 public:
  LinkedList() : size(0), head(NULL), tail(NULL) {}
  LinkedList(const LinkedList & rhs) : size(rhs.size), head(NULL), tail(NULL) {
    Node * dummy = rhs.head;
    if (dummy == NULL) {
      return;
    }
    else {
      head = new Node(dummy->data, NULL, NULL);
      Node * newDummy = head;
      dummy = dummy->next;
      while (dummy != NULL) {
        Node * newNode = new Node(dummy->data, NULL, NULL);
        newDummy->next = newNode;
        newNode->prev = newDummy;
        newDummy = newNode;
        dummy = dummy->next;
      }
      tail = newDummy;
    }
  }
  ~LinkedList() {
    while (head != NULL) {
      Node * dummy = head->next;
      delete head;
      head = dummy;
    }
    tail = NULL;
    size = 0;
  }
  LinkedList & operator=(const LinkedList & rhs) {
    if (*this != &rhs) {
      LinkedList tmp(rhs);
      //delete old data
      while (head != NULL) {
        Node * dummy = head->next;
        delete head;
        head = dummy;
      }

      head = tmp.head;
      tail = tmp.tail;
      size = tmp.size;

      tmp.head = NULL;
      tmp.tail = NULL;
      tmp.size = 0;
    }
    return *this;
    //new..
    //delete old...
    //head->new head
  }
  void addFront(const T & item) {
    head = new Node(item, head, NULL);
    if (tail == NULL) {
      tail = head;
    }
    else {
      head->next->prev = head;
    }
    size++;
  }

  void addBack(const T & item) {
    tail = new Node(item, NULL, tail);
    if (head == NULL) {
      head = tail;
    }
    else {
      tail->prev->next = tail;
    }
    size++;
  }
  bool remove(const T & item) {
    int pos = find(item);
    if (pos == -1) {
      return false;
    }

    else {
      Node * dummy = head;
      while (pos > 0) {
        dummy = dummy->next;
        pos--;
      }
      //dummy is the node to remove;
      if (dummy == head && dummy == tail) {
        head = NULL;
        tail = NULL;
      }
      else if (dummy == head) {
        dummy->next->prev = NULL;
        head = dummy->next;
      }
      else if (dummy == tail) {
        dummy->prev->next = NULL;
        tail = dummy->prev;
      }
      else {
        dummy->prev->next = dummy->next;
        dummy->next->prev = dummy->prev;
      }
      delete dummy;
      size--;
      return true;
    }
  }
  T & operator[](int index) {
    try {
      if (index >= size) {
        throw 0;
      }
      Node * dummy = head;
      for (int i = 0; i < index; ++i) {
        dummy = dummy->next;
      }
      return dummy->data;
    }
    catch (std::out_of_range & oor) {
      std::cerr << oor.what();
      exit(EXIT_FAILURE);
    }
  }

  const T & operator[](int index) const {
    try {
      if (index >= size) {
        throw 0;
      }
      Node * dummy = head;
      for (int i = 0; i < index; ++i) {
        dummy = dummy->next;
      }
      return dummy->data;
    }
    catch (std::out_of_range & oor) {
      std::cerr << oor.what();
      exit(EXIT_FAILURE);
    }
  }

  int find(const T & item) const {
    if (head == NULL) {
      return -1;
    }
    Node * dummy = head;
    int res = 0;
    while (dummy != NULL && dummy->data != item) {
      res++;
      dummy = dummy->next;
    }
    //didnot find
    if (!dummy)
      return -1;
    else
      return res;
  }

  int getSize() const { return size; }
};

#endif
