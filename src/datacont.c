
#include "include/datacont.h"


datacont* datacont_new(const void* data, const enum dataconttype dct, const size_t size)
{
  if (data == NULL || size == 0) return NULL;

  datacont* dc = malloc(sizeof(datacont));
  dc->type = dct;
  dc->size = size;

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
      dc->cp = malloc(sizeof(char) * size);
      memcpy(dc->cp, data, sizeof(char) * size);
      break;
    case SHORTP:
      dc->sp = malloc(sizeof(short) * size);
      memcpy(dc->sp, data, sizeof(short) * size);
      break;
    case INTP:
      dc->ip = malloc(sizeof(int) * size);
      memcpy(dc->ip, data, sizeof(int) * size);
      break;
    case LLP:
      dc->llp = malloc(sizeof(long long) * size);
      memcpy(dc->llp, data, sizeof(long long) * size);
      break;
    case FLOATP:
      dc->fp = malloc(sizeof(float) * size);
      memcpy(dc->fp, data, sizeof(float) * size);
      break;
    case DOUBLEP:
      dc->dp = malloc(sizeof(double) * size);
      memcpy(dc->dp, data, sizeof(double) * size);
      break;
    case UCHARP:
      dc->ucp = malloc(sizeof(unsigned char) * size);
      memcpy(dc->ucp, data, sizeof(char) * size);
      break;
    case USHORTP:
      dc->usp = malloc(sizeof(unsigned short) * size);
      memcpy(dc->usp, data, sizeof(short) * size);
      break;
    case UINTP:
      dc->uip = malloc(sizeof(unsigned int) * size);
      memcpy(dc->uip, data, sizeof(int) * size);
      break;
    case ULLP:
      dc->ullp = malloc(sizeof(unsigned long long) * size);
      memcpy(dc->ullp, data, sizeof(long long) * size);
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


datacont* datacont_copy(const datacont* dc)
{
  if (dc == NULL) return NULL;
  switch(dc->type)
  {
    case CHAR:
      return datacont_new(&(dc->c), dc->type, dc->size);
    case SHORT:
      return datacont_new(&(dc->s), dc->type, dc->size);
    case INT:
      return datacont_new(&(dc->i), dc->type, dc->size);
    case LL:
      return datacont_new(&(dc->ll), dc->type, dc->size);
    case FLOAT:
      return datacont_new(&(dc->f), dc->type, dc->size);
    case DOUBLE:
      return datacont_new(&(dc->d), dc->type, dc->size);
    case UCHAR:
      return datacont_new(&(dc->uc), dc->type, dc->size);
    case USHORT:
      return datacont_new(&(dc->us), dc->type, dc->size);
    case UINT:
      return datacont_new(&(dc->ui), dc->type, dc->size);
    case ULL:
      return datacont_new(&(dc->ull), dc->type, dc->size);
    case CHARP:
      return datacont_new(dc->cp, dc->type, dc->size);
    case SHORTP:
      return datacont_new(dc->sp, dc->type, dc->size);
    case INTP:
      return datacont_new(dc->ip, dc->type, dc->size);
    case FLOATP:
      return datacont_new(dc->fp, dc->type, dc->size);
    case DOUBLEP:
      return datacont_new(dc->dp, dc->type, dc->size);
    case UCHARP:
      return datacont_new(dc->ucp, dc->type, dc->size);
    case USHORTP:
      return datacont_new(dc->usp, dc->type, dc->size);
    case UINTP:
      return datacont_new(dc->uip, dc->type, dc->size);
    case ULLP:
      return datacont_new(dc->ullp, dc->type, dc->size);
  }
  return NULL;
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
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->cp[i] < dcb->cp[i]) return LESSTHAN;
	else if (dca->cp[i] > dcb->cp[i]) return GREATERTHAN;
      }
      break;
    case SHORTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->sp[i] < dcb->sp[i]) return LESSTHAN;
	else if (dca->sp[i] > dcb->sp[i]) return GREATERTHAN;
      }
      break;
    case INTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->ip[i] < dcb->ip[i]) return LESSTHAN;
	else if (dca->ip[i] > dcb->ip[i]) return GREATERTHAN;
      }
      break;
    case LLP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->llp[i] < dcb->llp[i]) return LESSTHAN;
	else if (dca->llp[i] > dcb->llp[i]) return GREATERTHAN;
      }
      break;
    case FLOATP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->fp[i] < dcb->fp[i]) return LESSTHAN;
	else if (dca->fp[i] > dcb->fp[i]) return GREATERTHAN;
      }
      break;
    case DOUBLEP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->dp[i] < dcb->dp[i]) return LESSTHAN;
	else if (dca->dp[i] > dcb->dp[i]) return GREATERTHAN;
      }
      break;
    case UCHARP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->ucp[i] < dcb->ucp[i]) return LESSTHAN;
	else if (dca->ucp[i] > dcb->ucp[i]) return GREATERTHAN;
      }
      break;
    case USHORTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->usp[i] < dcb->usp[i]) return LESSTHAN;
	else if (dca->usp[i] > dcb->usp[i]) return GREATERTHAN;
      }
      break;
    case UINTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->uip[i] < dcb->uip[i]) return LESSTHAN;
	else if (dca->uip[i] > dcb->uip[i]) return GREATERTHAN;
      }
      break;
    case ULLP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->ullp[i] < dcb->ullp[i]) return LESSTHAN;
	else if (dca->ullp[i] > dcb->ullp[i]) return GREATERTHAN;
      }
      break;
  }
  if (dca->size < dcb->size) return LESSTHAN;
  else if (dca->size > dcb->size) return GREATERTHAN;
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


static uint32_t __hash(const void* data, const size_t size)
{
  uint32_t seed = 2147483647;

  for (int i = 0; i < size; i++)
  {
	  uint8_t byte = *((uint8_t*) data + i);
	  seed = ((seed * byte) << 16) + ((seed * byte) >> 16);
  }
  return seed;
}


uint32_t datacont_hash(const datacont* dc)
{
  switch(dc->type)
  {
    case CHAR:
    case UCHAR:
      return __hash(&dc->c, sizeof(char));
    case SHORT:
    case USHORT:
      return __hash(&dc->s, sizeof(short));
    case INT:
    case UINT:
      return __hash(&dc->i, sizeof(int));
    case LL:
    case ULL:
      return __hash(&dc->ll, sizeof(long long));
    case FLOAT:
      return __hash(&dc->f, sizeof(float));
    case DOUBLE:
      return __hash(&dc->d, sizeof(double));
    case CHARP:
      return __hash(dc->cp, sizeof(char) * dc->size);
    case SHORTP:
      return __hash(dc->sp, sizeof(short) * dc->size);
    case INTP:
      return __hash(dc->ip, sizeof(int) * dc->size);
    case LLP:
      return __hash(dc->llp, sizeof(long long) * dc->size);
    case FLOATP:
      return __hash(dc->fp, sizeof(float) * dc->size);
    case DOUBLEP:
      return __hash(dc->dp, sizeof(double) * dc->size);
  }
}


