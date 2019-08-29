
#include <stdlib.h>
#include <string.h>

#include "include/datacont.h"


datacont* datacont_new(const void* data, const enum dataconttype dct, const unsigned int count)
{
  datacont* dc = (datacont*) malloc(sizeof(datacont));
  dc->type = dct;
  dc->count = count;
  switch(dct)
  {
    case CHAR:
      dc->c = *((char*) data);
      break;
    case SHORT:
      dc->s = *((short*) data);
      break;
    case INT:
      dc->i = *((int*) data);
      break;
    case LL:
      dc->ll = *((long long*) data);
      break;
    case FLOAT:
      dc->f = *((float*) data);
      break;
    case DOUBLE:
      dc->d = *((double*) data);
      break;
    case UCHAR:
      dc->uc = *((unsigned char*) data);
      break;
    case USHORT:
      dc->us = *((unsigned short*) data);
      break;
    case UINT:
      dc->ui = *((unsigned int*) data);
      break;
    case ULL:
      dc->ull = *((unsigned long long*) data);
      break;
    case CHARP:
      dc->cp = malloc(sizeof(char) * count);
      memcpy(dc->cp, data, sizeof(char) * count);
      break;
    case SHORTP:
      dc->sp = malloc(sizeof(short) * count); 
      memcpy(dc->sp, data, sizeof(short) * count);
      break;
    case INTP:
      dc->ip = malloc(sizeof(int) * count);
      memcpy(dc->ip, data, sizeof(int) * count);
      break;
    case LLP:
      dc->llp = malloc(sizeof(long long) * count);
      memcpy(dc->llp, data, sizeof(long long) * count);
      break;
    case FLOATP:
      dc->fp = malloc(sizeof(float) * count);
      memcpy(dc->fp, data, sizeof(float) * count);
      break;
    case DOUBLEP:
      dc->dp = malloc(sizeof(double) * count);
      memcpy(dc->dp, data, sizeof(double) * count);
      break;
    case UCHARP:
      dc->ucp = malloc(sizeof(unsigned char) * count);
      memcpy(dc->ucp, data, sizeof(char) * count);
      break;
    case USHORTP:
      dc->usp = malloc(sizeof(unsigned short) * count);
      memcpy(dc->usp, data, sizeof(short) * count);
      break;
    case UINTP:
      dc->uip = malloc(sizeof(unsigned int) * count);
      memcpy(dc->uip, data, sizeof(int) * count);
      break;
    case ULLP:
      dc->ullp = malloc(sizeof(unsigned long long) * count);
      memcpy(dc->ullp, data, sizeof(long long) * count);
      break;
  }
  return dc;
}


static enum datacontcomp _compare_single_items(const datacont* dca, const datacont* dcb)
{
  switch(dca->type)
  {
    case CHAR:
      if (dca->c == dcb->c) return EQUAL;
      else if (dca->c < dcb->c) return LESSTHAN;
      else return GREATERTHAN;
    case SHORT:
      if (dca->s == dcb->s) return EQUAL;
      else if (dca->s < dcb->s) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case INT:
      if (dca->i == dcb->i) return EQUAL;
      else if (dca->i < dcb->i) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case LL:
      if (dca->ll == dcb->ll) return EQUAL;
      else if (dca->ll < dcb->ll) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case FLOAT:
      if (dca->f == dcb->f) return EQUAL;
      else if (dca->f < dcb->f) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case DOUBLE:
      if (dca->d == dcb->d) return EQUAL;
      else if (dca->d < dcb->d) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case UCHAR:
      if (dca->uc == dcb->uc) return EQUAL;
      else if (dca->uc < dcb->uc) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case USHORT:
      if (dca->us == dcb->us) return EQUAL;
      else if (dca->us < dcb->us) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case UINT:
      if (dca->ui == dcb->ui) return EQUAL;
      else if (dca->ui < dcb->ui) return LESSTHAN;
      else return GREATERTHAN;
      break;
    case ULL:
      if (dca->ull == dcb->ull) return EQUAL;
      else if (dca->ull < dcb->ull) return LESSTHAN;
      else return GREATERTHAN;
      break;
  }
  return CANTCOMPARE;
}


static enum datacontcomp _compare_multi_items(const datacont* dca, const datacont* dcb)
{
  switch(dca->type)
  {
    case CHARP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->cp[i] < dcb->cp[i]) return LESSTHAN;
	else if (dca->cp[i] > dcb->cp[i]) return GREATERTHAN;
      }
      break;
    case SHORTP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->sp[i] < dcb->sp[i]) return LESSTHAN;
	else if (dca->sp[i] > dcb->sp[i]) return GREATERTHAN;
      }
      break;
    case INTP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->ip[i] < dcb->ip[i]) return LESSTHAN;
	else if (dca->ip[i] > dcb->ip[i]) return GREATERTHAN;
      }
      break;
    case LLP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->llp[i] < dcb->llp[i]) return LESSTHAN;
	else if (dca->llp[i] > dcb->llp[i]) return GREATERTHAN;
      }
      break;
    case FLOATP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->fp[i] < dcb->fp[i]) return LESSTHAN;
	else if (dca->fp[i] > dcb->fp[i]) return GREATERTHAN;
      }
      break;
    case DOUBLEP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->dp[i] < dcb->dp[i]) return LESSTHAN;
	else if (dca->dp[i] > dcb->dp[i]) return GREATERTHAN;
      }
      break;
    case UCHARP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->ucp[i] < dcb->ucp[i]) return LESSTHAN;
	else if (dca->ucp[i] > dcb->ucp[i]) return GREATERTHAN;
      }
      break;
    case USHORTP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->usp[i] < dcb->usp[i]) return LESSTHAN;
	else if (dca->usp[i] > dcb->usp[i]) return GREATERTHAN;
      }
      break;
    case UINTP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->uip[i] < dcb->uip[i]) return LESSTHAN;
	else if (dca->uip[i] > dcb->uip[i]) return GREATERTHAN;
      }
      break;
    case ULLP:
      for (int i = 0; i < dca->count && i < dcb->count; i++)
      {
        if (dca->ullp[i] < dcb->ullp[i]) return LESSTHAN;
	else if (dca->ullp[i] > dcb->ullp[i]) return GREATERTHAN;
      }
      break;
  }
  if (dca->count < dcb->count) return LESSTHAN;
  else if (dca->count > dcb->count) return GREATERTHAN;
  else return EQUAL;
}


enum datacontcomp datacont_compare(const datacont* dca, const datacont* dcb)
{
  if (dca->type != dcb->type)
    return CANTCOMPARE;
  
  if (dca->type < CHARP)
    return _compare_single_items(dca, dcb);
  else return _compare_multi_items(dca, dcb);
}


void datacont_delete(datacont* dc)
{
  if (dc == NULL) return;
  if (dc->type < CHARP)
    return free(dc);
  free(dc->cp);
  free(dc);
}

unsigned long long datacont_hash(unsigned long long seed, const datacont* dc)
{
  unsigned long long hashval;
  switch(dc->type)
  {
    case CHAR:
    case UCHAR:
      hashval = hash(seed, &dc->c, sizeof(char));
      break;
    case SHORT:
    case USHORT:
      hashval = hash(seed, &dc->s, sizeof(short));
      break;
    case INT:
    case UINT:
      hashval = hash(seed, &dc->i, sizeof(int));
      break;
    case LL:
    case ULL:
      hashval = hash(seed, &dc->ll, sizeof(long long));
      break;
    case FLOAT:
      hashval = hash(seed, &dc->f, sizeof(float));
      break;
    case DOUBLE:
      hashval = hash(seed, &dc->d, sizeof(double));
      break;
    case CHARP:
      hashval = hash(seed, dc->cp, sizeof(char) * dc->count);
      break;
    case SHORTP:
      hashval = hash(seed, dc->sp, sizeof(short) * dc->count);
      break;
    case INTP:
      hashval = hash(seed, dc->ip, sizeof(int) * dc->count);
      break;
    case LLP:
      hashval = hash(seed, dc->llp, sizeof(long long) * dc->count);
      break;
    case FLOATP:
      hashval = hash(seed, dc->fp, sizeof(float) * dc->count);
      break;
    case DOUBLEP:
      hashval = hash(seed, dc->dp, sizeof(double) * dc->count);
      break;
  }
  return hashval;
}

