#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <string>
#include "fraction.h"

using namespace std;

const int
  TABLE_SIZE = 101,
  TABLE_LIMIT = 75;

enum DictionaryStatus {
  STATUS_UNUSED,
  STATUS_INUSE,
  STATUS_DELETED
};

class Dictionary {
 public:
  Dictionary();
  ~Dictionary() { }

  void clear();

  bool isEmpty() { return !count; }
  int size() { return count; }

  Fraction search(string key);
  void update(string key,Fraction value);
  void insert(string key,Fraction value);
  void remove(string key);

 private:
  string
    keys[TABLE_SIZE];
  Fraction
    values[TABLE_SIZE];
  DictionaryStatus
    status[TABLE_SIZE];
  int
    count;
};

#endif