/*
 * dot -Tpng -o <outfile> <infile>
 */

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <kylestructs/hash.h>
#include <kylestructs/datacont.h>
#include <kylestructs/treenode.h>
#include <kylestructs/treeset.h>
#include <kylestructs/hashset.h>

#define FLOOR(N) ((long long) N)

unsigned int snum_len(signed long long num, unsigned char base)
{
  unsigned int len = 1;
  while(num /= base) len++;
  return len;
}


unsigned int unum_len(unsigned long long num, unsigned char base)
{
  unsigned int len = 1;
  while(num /= base) len++;
  return len;
}


void datacont_to_string(datacont* dc, char* buffer)
{
  switch(dc->type)
  {
    case CHAR:
      sprintf(buffer, "%c", dc->c);
      break;
    case SHORT:
      sprintf(buffer, "%hi", dc->s);
      break;
    case INT:
      sprintf(buffer, "%i", dc->i);
      break;
    case LL:
      sprintf(buffer, "%lli", dc->ll);
      break;
    case FLOAT:
      sprintf(buffer, "%.5f", dc->f);
      break;
    case DOUBLE:
      sprintf(buffer, "%.5lf", dc->d);
      break;
    case UCHAR:
      sprintf(buffer, "%hhu", dc->uc);
      break;
    case USHORT:
      sprintf(buffer, "%hu", dc->us);
      break;
    case UINT:
      sprintf(buffer, "%u", dc->i);
      break;
    case ULL:
      sprintf(buffer, "%llu", dc->ull);
      break;
    case CHARP:
      sprintf(buffer, "%s", dc->cp);
      break;
    default:
      buffer[0] = '[';
      int currlen = 1;
      int numlen = 0, i = 0;
      for (; i < dc->count; i++)
      {
	/* for integer values, add 2 to numlen to account for
	 * ',' and ' ' (space) at end of value.
	 * for floating point values, add 5 -- 2 for ',' and
	 * ' ', and 3 for '.00' sig digs
	 */
	switch(dc->type)
	{
          case SHORTP: numlen = snum_len(dc->sp[i], 10) + 2; break;
          case INTP: numlen = snum_len(dc->ip[i], 10) + 2; break;
          case LLP: numlen = snum_len(dc->llp[i], 10) + 2; break;
	  case FLOATP: numlen = snum_len(FLOOR(dc->fp[i]), 10) + 5; break;
          case DOUBLEP: numlen = snum_len(FLOOR(dc->dp[i]), 10) + 5; break;
	  case UCHARP: numlen = unum_len(dc->ucp[i], 10) + 2; break;
          case USHORTP: numlen = unum_len(dc->usp[i], 10) + 2; break;
	  case UINTP: numlen = unum_len(dc->uip[i], 10) + 2; break;
          case ULLP: numlen = unum_len(dc->ullp[i], 10) + 2; break;
	}
        if (currlen + numlen > 27) break;
        switch(dc->type)
	{
	  case SHORTP: sprintf( &(buffer[currlen]), "%hi, ", dc->sp[i]); break;
	  case INTP: sprintf( &(buffer[currlen]), "%i, ", dc->ip[i]); break;
	  case LLP: sprintf( &(buffer[currlen]), "%lli, ", dc->llp[i]); break;
	  case FLOATP: sprintf( &(buffer[currlen]), "%.2f, ", dc->fp[i]); break;
	  case DOUBLEP: sprintf( &(buffer[currlen]), "%.2lf, ", dc->dp[i]); break;
	  case UCHARP: sprintf( &(buffer[currlen]), "%hhu, ", dc->ucp[i]); break;
	  case USHORTP: sprintf( &(buffer[currlen]), "%hu, ", dc->usp[i]); break;
	  case UINTP: sprintf( &(buffer[currlen]), "%u, ", dc->uip[i]); break;
	  case ULLP: sprintf( &(buffer[currlen]), "%llu, ", dc->ullp[i]); break;
	}
	currlen += numlen;
      }
      if (i < dc->count)
	currlen--; // put period in place of last space
        for (int j = 0; j < 3 && j+currlen < 27; j++)
          buffer[currlen++] = '.';
      buffer[currlen++] = ']';
      buffer[currlen] = '\0';
      break;
  }
}


static void _generate_dotfile(const treenode* tn)
{
  char buffer_parent[30];
  char buffer_child[30];
  datacont_to_string(tn->dc, buffer_parent);
  if (tn->left)
  {
    datacont_to_string(tn->left->dc, buffer_child);
    printf("\"%s\"->\"%s\"[color=blue];\n", buffer_parent, buffer_child);
    _generate_dotfile(tn->left);
  }
  if (tn->right)
  {
    datacont_to_string(tn->right->dc, buffer_child);
    printf("\"%s\"->\"%s\"[color=red];\n", buffer_parent, buffer_child);
    _generate_dotfile(tn->right);
  }
}


void generate_dotfile(const treenode* tn)
{
  char buffer_parent[30];
  char buffer_child[30];
  if (tn)
  {
    datacont_to_string(tn->dc, buffer_parent);
    printf("\"%s\";\n", buffer_parent);
    if (tn->left)
    {
      datacont_to_string(tn->left->dc, buffer_child);
      printf("\"%s\"->\"%s\"[color=blue];\n", buffer_parent, buffer_child);
      _generate_dotfile(tn->left);
    }
    if (tn->right)
    {
      datacont_to_string(tn->right->dc, buffer_child);
      printf("\"%s\"->\"%s\"[color=red];\n", buffer_parent, buffer_child);
      _generate_dotfile(tn->right);
    }
  }
  else printf("NULL;\n");
}


int main()
{
  srand(time(NULL));
  hashset* hs = hashset_new(3, rand());
  for (int i = 0; i < 50; i++)
  {
    short num = rand() % 1000;
    hashset_add(hs, datacont_new(&num, SHORT, 1));
  }
  
/*
  treeset* ts = treeset_new();
  for (int i = 0; i < 10; i++)
  {
    int numitems = (rand() % 5) + 1;
    float numlist[numitems];
    for (int j = 0; j < numitems; j++)
      numlist[j] = ((float) rand()) / (0.1 * RAND_MAX);

    treeset_add(ts, datacont_new(&numlist, FLOATP, numitems));
  }
*/
  /*
  treeset* ts = treeset_new();

  treeset_add(ts, datacont_new("BAZ", CHARP, 3));
  treeset_add(ts, datacont_new("FOO", CHARP, 3));
  treeset_add(ts, datacont_new("BAR", CHARP, 3));
  */
/*  printf("\ndigraph G {\n");
  printf("subgraph cluster_t {\n");
  printf("label = \"Treeset\";\n");
  generate_dotfile(ts->root);
  printf("}\n}\n\n");
*/
  
  printf("digraph G {\n");
  printf("subgraph cluster_h {\n");
  printf("label = \"Hashset\\lblue = 'less than'\\lred = 'greater than'\";");
  for (int i = 0; i < hs->num_buckets; i++)
  {
    printf("# tree in bucket %d:\n", i);
    printf("subgraph cluster_%d {\n", i);
    printf("label = \"Treeset in bucket %d\"\n", i);
    generate_dotfile(hs->buckets[i]->root);
    printf("}\n");
  }
  printf("}\n}\n");
  
  return 0;
}


