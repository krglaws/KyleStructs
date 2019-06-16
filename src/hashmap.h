
#ifndef _HASHMAP_
#define _HASHMAP_

#define BUCKETS 100

typedef struct hashmap_t {
  treenode* buckets[BUCKETS];
} hashmap;

unsigned long hash(unsigned char *str);

int add_to_map(hashmap* map, char* word);

int map_contains(hashmap* map, char* word);

hashmap* new_hashmap(int num_words, char** words);

#endif
