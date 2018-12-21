#include <exceptions.h>
#include "dictionary.h"

static unsigned int hashStr(string key) {
  unsigned int result = 0;

  for (unsigned int i=0;i<key.length();i++)
    result = result * i + key[i];

  return result % TABLE_SIZE;
}

Dictionary::Dictionary() {

  clear();
}

void Dictionary::clear() {

  for (count=0;count<TABLE_SIZE;count++)
    status[count] = STATUS_UNUSED;

  count = 0;
}

Fraction Dictionary::search(string key) {
  unsigned int
    pos = hashStr(key);

  while (status[pos] != STATUS_UNUSED) {
    if (status[pos] == STATUS_INUSE && keys[pos] == key)
      return values[pos];
    pos = ++pos % TABLE_SIZE;
  }

  throw KeyNotFoundException(key);
}

void Dictionary::update(string key,Fraction value) {
  unsigned int
    pos = hashStr(key);

  while (status[pos] != STATUS_UNUSED) {
    if (status[pos] == STATUS_INUSE && keys[pos] == key) {
      values[pos] = value;
      return;
    }
    pos = ++pos % TABLE_SIZE;
  }

  throw KeyNotFoundException(key);
}

void Dictionary::insert(string key,Fraction value) {
  unsigned int
    pos = hashStr(key),
    dest = -1;

  if (count == TABLE_LIMIT)
    throw ContainerFullException();

  while (status[pos] != STATUS_UNUSED) {
    if (status[pos] == STATUS_DELETED && dest == -1)
      dest = pos;
    if (status[pos] == STATUS_INUSE && keys[pos] == key)
      throw DuplicateKeyException(key);
    pos = ++pos % TABLE_SIZE;
  }

  if (dest == -1)
    dest = pos;

  keys[dest] = key;
  values[dest] = value;
  status[dest] = STATUS_INUSE;
}

void Dictionary::remove(string key) {
  unsigned int
    pos = hashStr(key);

  while (status[pos] != STATUS_UNUSED) {
    if (status[pos] == STATUS_INUSE && keys[pos] == key) {
      status[pos] = STATUS_DELETED;
      return;
    }
    pos = ++pos % TABLE_SIZE;
  }

  throw KeyNotFoundException(key);
}