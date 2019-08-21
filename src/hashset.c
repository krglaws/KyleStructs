#include <stdlib.h>

#include "tree.h"
#include "hashmap.h"


unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}


int add_to_map(hashmap* map, char* word)
{
  unsigned int hashval = hash(word);
  if (map->buckets[hashval % BUCKETS] == NULL)
  {
    map->buckets[hashval % BUCKETS] = build_binary_tree(1, &word);
    return 0;
  }
  else insert_node(map->buckets[hashval % BUCKETS], word);
  return 1; // collision
}


int map_contains(hashmap* map, char* word)
{
  if (!map || !word) return 0;
  unsigned int hashval = hash(word);
  if (map->buckets[hashval % BUCKETS] == NULL)
    return 0;
  else if (in_tree(map->buckets[hashval % BUCKETS], word))
    return 1;
  return 0;
}


hashmap* new_hashmap(int num_words, char** words)
{
  hashmap* map = (hashmap*)calloc(1, sizeof(hashmap));
  if (!words || !num_words) return map;
  for (int i = 0; i < num_words; i++)
    add_to_map(map, words[i]);
  return map;
}
