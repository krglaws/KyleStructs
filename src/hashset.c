#include <stdlib.h>

#include "treeset.h"
#include "hashset.h"


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash;
}


int hashset_add(hashset* hs, char* word)
{
  unsigned int hashval = hash(word);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
  {
    hs->buckets[hashval % hs->num_buckets] = treeset_new(1, word);
    return 0;
  }

  return treeset_add(hs->buckets[hashval % hs->num_buckets], word);
}


int hashset_remove(hashset* hs, char* word)
{
  unsigned int hashval = hash(word);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
    return 1;

  return treeset_remove(hs->buckets[hashval % hs->num_buckets], word);
}


int hashset_contains(hashset* hs, char* word)
{
  if (!hs || !word)
    return 0;

  unsigned int hashval = hash(word);

  if (hs->buckets[hashval % hs->num_buckets] == NULL)
    return 0;

  return treeset_contains(hs->buckets[hashval % hs->num_buckets], word)
}


hashset* hashset_new(int num_words, char** words)
{
  hashset* hs = (hashset*)calloc(1, sizeof(hashset));

  if (!words || !num_words) 
    return map;

  for (int i = 0; i < num_words; i++)
    hashset_add(hs, words[i]);

  return hs;
}


