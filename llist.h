#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <assert.h>
#include "node.h"

template <typename T>
class LinkedList{
private:
  int size;
  LNode<T> *head;
  LNode<T> *insert_in_order_helper(LNode<T> *root, const T &value);
  LNode<T> *remove_helper(LNode<T> *root, const T &value);
public:
  LinkedList();
  ~LinkedList();
  void insert(const T &value);
  void insert_in_order(const T &value);
  int find(const T &value);
  T &operator[](int index);
  void remove(const T &value);
  int get_size();
  void print();
};

template <typename T>
LinkedList<T>::LinkedList(): head(NULL), size(0){}

template <typename T>
LinkedList<T>::~LinkedList(){
  delete head;
}

template <typename T>
void LinkedList<T>::insert(const T &value){
  head = new LNode<T>(value, head);
  size++;
}

template <typename T>
void LinkedList<T>::insert_in_order(const T &value){
  head = insert_in_order_helper(head, value);
  size++;
}

template <typename T>
LNode<T>* LinkedList<T>::insert_in_order_helper(LNode<T> *root, const T &value){
  if(root == NULL || root->value > value) return new LNode<T>(value, root);
  else root->next = insert_in_order_helper(root->next, value);
  return root;
}

template <typename T>
int LinkedList<T>::find(const T &value){
  int index = 0;
  for(LNode<T>* cur = head; cur; cur = cur->next){
    if(cur->value == value)
      return index;
    index++;
  }
  return -1;
}

template <typename T>
T &LinkedList<T>::operator[](int index){
  assert(index < size);

  LNode<T>* cursor = head;
  for(int i = 0; i < index; i++) cursor = cursor->next;

  return cursor->value;
}

template <typename T>
void LinkedList<T>::remove(const T &value){
  assert(find(value) != -1);
  head = remove_helper(head, value);
}

template <typename T>
LNode<T> *LinkedList<T>::remove_helper(LNode<T> *root, const T &value){
  if(root->value == value){
    LNode<T> *temp = root->next;
    root->next = NULL;
    delete root;
    return temp;
  }
  else{
    root->next = remove_helper(root->next, value);
    return root;
  }
}

template <typename T>
int LinkedList<T>::get_size(){
  return size;
}

template <typename T>
void LinkedList<T>::print(){
  for(LNode<T>* cur = head; cur; cur = cur->next)
    cout << cur->value << endl;
}

#endif
