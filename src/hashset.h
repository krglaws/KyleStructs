
#include "treeset.h"

#ifndef _HASHSET_H_
#define _HASHSET_H_

typedef struct {
  unsigned int num_buckets;
  treeset** buckets;
} hashset;

unsigned long hash(unsigned char *str);

int hashset_add(hashset* hs, char* word);

int hashset_remove(hahset* hs, char* word);

int hashset_contains(hashset* hs, char* word);

hashset* hashset_new(int num_words, char** words);

#endif
