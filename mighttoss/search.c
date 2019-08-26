#include "search.h"


int linear_compare(char* word, char* query)
{
  int len1 = strlen(word);
  int len2 = strlen(query);
  if (len1 != len2) return 0;
  for (int i = 0; i < len1; i++)
    if (word[i] != query[i] && query[i] != '.')
      return 0;
  return 1;
}


int linear_search(int num_words, char** words, char* query)
{
  for (int i = 0; i < num_words; i++)
    if (linear_compare(words[i], query)) return 1;
  return 0;
}


int binary_search(int num_words, char** words, char* query)
{
  return 0;
}
