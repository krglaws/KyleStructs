
#ifndef _HASHSET_H_
#define _HASHSET_H_

typedef struct hashset hashset;

struct hashset {
  const unsigned int num_buckets;
  treeset** buckets;
};

const unsigned int hash(const char *str);

int hashset_add(hashset* hs, const char* word);

int hashset_remove(hashset* hs, const char* word);

int hashset_contains(const hashset* hs, const char* word);

hashset* hashset_new(const unsigned int num_words, const char** words);

#endif
