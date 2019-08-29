
#include <stdlib.h>
#include <string.h>

#include "include/hash.h"
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


void datacont_delete(datacont* dc)
{
  if (dc == NULL) return;
  if (dc->type < CHARP)
    free(dc);
  else
  {
    free(dc->cp);
    free(dc);
  }
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


unsigned long long datacont_hash(unsigned long long seed, const datacont* dc)
{
  switch(dc->type)
  {
    case CHAR:
    case UCHAR:
      return hash(seed, &dc->c, sizeof(char));
    case SHORT:
    case USHORT:
      return hash(seed, &dc->s, sizeof(short));
    case INT:
    case UINT:
      return hash(seed, &dc->i, sizeof(int));
    case LL:
    case ULL:
      return hash(seed, &dc->ll, sizeof(long long));
    case FLOAT:
      return hash(seed, &dc->f, sizeof(float));
    case DOUBLE:
      return hash(seed, &dc->d, sizeof(double));
    case CHARP:
      return hash(seed, dc->cp, sizeof(char) * dc->count);
    case SHORTP:
      return hash(seed, dc->sp, sizeof(short) * dc->count);
    case INTP:
      return hash(seed, dc->ip, sizeof(int) * dc->count);
    case LLP:
      return hash(seed, dc->llp, sizeof(long long) * dc->count);
    case FLOATP:
      return hash(seed, dc->fp, sizeof(float) * dc->count);
    case DOUBLEP:
      return hash(seed, dc->dp, sizeof(double) * dc->count);
  }
  /* should figure out some way to report error */
}
