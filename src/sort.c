#include "sort.h"
#include "main.h"
#include <stdio.h>

void bubble_sort(int num_words, char** words)
{
  for (int i = 0; i < num_words; i++)
  {
    int sorted = 1;
    for (int j = 0; j < num_words-1-i; j++)
      if(strcmp(words[j], words[j+1]) > 0)
      {
        sorted = 0;
        char* temp = words[j];
        words[j] = words[j+1];
        words[j+1] = temp;
      }
    if (sorted) return;
  }
}


void _merge_sort(char** words, int low, int high)
{
  if (low == high) return;
  int mid = (high + low) / 2;
  int size = (high + 1) - low;

  _merge_sort(words, low, mid);
  _merge_sort(words, mid+1, high);

  int l = low;
  int r = mid+1;
  char* temp[size];
  for (int i = 0; i < size; i++)
    if (r > high)
      temp[i] = words[l++];
    else if (l > mid)
      temp[i] = words[r++];
    else temp[i] = strcmp(words[l], words[r]) < 0 ? words[l++] : words[r++];

  for (int i = 0; i < size; i++)
    words[i+low] = temp[i];
}


void merge_sort(int num_words, char** words)
{
  _merge_sort(words, 0, num_words-1);
}


int partition(char** words, int left, int right, char* pivot)
{
  while (left < right)
  {
    while (strcmp(pivot, words[left]) > 0) left++;
    while (strcmp(pivot, words[right]) < 0) right--;
    if (left < right)
    {
      char* temp = words[left];
      words[left] = words[right];
      words[right] = temp;
    }
  }
  return left;
}


void _quick_sort(char** words, int left, int right)
{
  if (left >= right) return;
  char* pivot = words[(right+left)/2];
  int part = partition(words, left, right, pivot);
  _quick_sort(words, left, part);
  _quick_sort(words, part+1, right);
}

void quick_sort(int num_words, char** words)
{
  _quick_sort(words, 0, num_words-1);
}
