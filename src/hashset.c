
#include <stdlib.h>

#include "treeset.h"
#include "hashset.h"


const unsigned int hash(const char *str)
{
    unsigned int hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}


int hashset_add(hashset* hs, const char* word)
{
  const unsigned int hashval = hash(word);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
  {
    hs->buckets[hashval % hs->num_buckets] = treeset_new(1, &word);
    return 0;
  }

  return treeset_add(hs->buckets[hashval % hs->num_buckets], word);
}


int hashset_remove(hashset* hs, const char* word)
{
  const unsigned int hashval = hash(word);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
    return 1;

  return treeset_remove(hs->buckets[hashval % hs->num_buckets], word);
}


int hashset_contains(const hashset* hs, const char* word)
{
  if (hs == NULL || word == NULL)
    return 0;

  unsigned int hashval = hash(word);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
    return 0;

  return treeset_contains(hs->buckets[hashval % hs->num_buckets], word);
}


hashset* hashset_new(const unsigned int num_words, const char** words)
{
  hashset* hs = (hashset*)calloc(1, sizeof(hashset));

  if (words == NULL || num_words == 0) 
    return hs;

  for (int i = 0; i < num_words; i++)
    hashset_add(hs, words[i]);

  return hs;
}


