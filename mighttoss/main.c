/*
 * dot -Tpng -o <outfile> <infile>
 */

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "search.h"
#include "sort.h"
#include "tree.h"
#include "hashmap.h"

#include "main.h"


int is_member(int num_words, char** words, char* query)
{
  return linear_search(num_words, words, query);
}


void print_words(int num_words, char** words, char* title)
{
  printf("%s\n", title);
  for (int i = 0; i < num_words; i++)
    printf("%s   ", words[i]);
}


char* random_word(int max_len)
{
  int len, j=0;
  char* word;
  len = (rand() % (max_len-1)) + 1;
  word = (char*) malloc(len*sizeof(char));
  for (; j < len; j++) word[j] = (char) (rand() % 26) + 'A';
  word[j] = 0;
  return word;
}


char** random_words(int num_words, int max_len)
{
  srand(time(NULL));
  char** words = (char**) malloc(sizeof(char**)*num_words);
  for (int i = 0; i < num_words; i++)
    words[i] = random_word(max_len);
  return words;
}


void usage()
{
  printf("exe <num_words> <1=bubble_sort, 2=merge_sort, 3=q_sort>\n");
  exit(0);
}


int main(int argc, char** argv)
{
  int max_len = 11;
  int num_words;

  if (argc < 3) usage();
  num_words = strtol(argv[1], 0, 10);
  char**words = random_words(num_words, max_len);
  hashmap* map = new_hashmap(num_words, words);

  printf("digraph G {\n");
  for (int i = 0; i < BUCKETS; i++)
  {
    printf("# tree in bucket %d:\n", i);
    generate_dotfile(map->buckets[i]);
  }
  printf("}\n\n");
  return 0;
}
