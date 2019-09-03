
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/include/datacont.h"
#include "../src/include/treenode.h"


unsigned int snum_len(signed long long num)
{
  unsigned int len = 1;
  while(num /= 10) len++;
  return len;
}

unsigned 


char* sitoa(long long num, char* buffer)
{
  int len = num_len(num);
  
  int i = len-1;
  while(num && i >= 0)
  {
    str[i--] = (num % 10) + 0x30;
    num /= 10;
  }
  
  return str;
}


int main(int argc, char** argv)
{
	for (int i = 1; i < argc; i++)
	{
		long long num = strtol(argv[i], NULL, 10);
		char* str = itoa(num);
		printf("len(%s) = %d\n", str, strlen(str));
	}
}


/*
const char* datactont_to_string(dc)
{
  char* result;
  switch(dc->type)
  {
    case CHAR:
      result = (char*)malloc(sizeof(char));
      result* = dc->c;
      break;
    case SHORT:
      result = (char*)malloc(sizeof(short));
      result* = dc->s;
      break;
    case INT:
      result = char*
      
}


static void _generate_dotfile(const treenode* tn)
{
  if (tn->right)
  {
    printf("%s->%s[color=red];\n", tn->dc, tn->right->word);
    _generate_dotfile(tn->right);
  }
  if (tn->left)
  {
    printf("%s->%s[color=blue];\n", tn->dc, tn->left->word);
    _generate_dotfile(tn->left);
  }
}


void generate_dotfile(const treenode* tn)
{
  if (tn)
  {
    printf("%s;\n", tn->dc);
    if (tn->right)
    {
      printf("%s->%s[color=red];\n", tn->dc, tn->right->word);
      _generate_dotfile(tn->right);
    }
    if (tn->left)
    {
      printf("%s->%s[color=blue];\n", tn->dc, tn->left->word);
      _generate_dotfile(tn->left);
    }
  }
  else printf("NULL;\n");
}
*/
