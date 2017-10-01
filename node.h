#ifndef NODE_H
#define NODE_H

#include <string>

using namespace std;

template <typename T>
struct LNode
{
  T value;
  LNode *next;
  LNode(const T &v, LNode *n)
      : value(v), next(n)
  {
  }

  LNode()
      : value(T()), next(NULL)
  {
  }
  ~LNode()
  {
    delete next;
  }
  LNode(const LNode<T> &rhs)
  {
    value = rhs.value;
    next = rhs.next;
  }
};

template <typename T>
struct DictionaryNode
{
  string key;
  T value;
  DictionaryNode *next;
  DictionaryNode(string k, const T &v, DictionaryNode *n)
      : key(k), value(v), next(n)
  {
  }

  DictionaryNode()
      : key(""), value(T()), next(NULL)
  {
  }
  ~DictionaryNode()
  {
  }
  DictionaryNode(const DictionaryNode<T> &rhs)
  {
    key = rhs.key;
    value = rhs.value;
    next = rhs.next;
  }
};

#endif
