#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <ks_datacont.h>


ks_datacont* ks_datacont_new(const void* data, const enum ks_datatype dct, const size_t size)
{
  if (data == NULL || size == 0) return NULL;

  ks_datacont* dc = malloc(sizeof(ks_datacont));
  dc->type = dct;
  dc->size = size;

  switch(dct)
  {
    case KS_CHAR:
      dc->c = *((char*) data);
      break;
    case KS_SHORT:
      dc->s = *((short*) data);
      break;
    case KS_INT:
      dc->i = *((int*) data);
      break;
    case KS_LL:
      dc->ll = *((long long*) data);
      break;
    case KS_FLOAT:
      dc->f = *((float*) data);
      break;
    case KS_DOUBLE:
      dc->d = *((double*) data);
      break;
    case KS_UCHAR:
      dc->uc = *((unsigned char*) data);
      break;
    case KS_USHORT:
      dc->us = *((unsigned short*) data);
      break;
    case KS_UINT:
      dc->ui = *((unsigned int*) data);
      break;
    case KS_ULL:
      dc->ull = *((unsigned long long*) data);
      break;
    case KS_CHARP:
      dc->cp = calloc(1, (sizeof(char) * size) + 1);
      memcpy(dc->cp, data, sizeof(char) * size);
      break;
    case KS_SHORTP:
      dc->sp = malloc(sizeof(short) * size);
      memcpy(dc->sp, data, sizeof(short) * size);
      break;
    case KS_INTP:
      dc->ip = malloc(sizeof(int) * size);
      memcpy(dc->ip, data, sizeof(int) * size);
      break;
    case KS_LLP:
      dc->llp = malloc(sizeof(long long) * size);
      memcpy(dc->llp, data, sizeof(long long) * size);
      break;
    case KS_FLOATP:
      dc->fp = malloc(sizeof(float) * size);
      memcpy(dc->fp, data, sizeof(float) * size);
      break;
    case KS_DOUBLEP:
      dc->dp = malloc(sizeof(double) * size);
      memcpy(dc->dp, data, sizeof(double) * size);
      break;
    case KS_UCHARP:
      dc->ucp = malloc(sizeof(unsigned char) * size);
      memcpy(dc->ucp, data, sizeof(char) * size);
      break;
    case KS_USHORTP:
      dc->usp = malloc(sizeof(unsigned short) * size);
      memcpy(dc->usp, data, sizeof(short) * size);
      break;
    case KS_UINTP:
      dc->uip = malloc(sizeof(unsigned int) * size);
      memcpy(dc->uip, data, sizeof(int) * size);
      break;
    case KS_ULLP:
      dc->ullp = malloc(sizeof(unsigned long long) * size);
      memcpy(dc->ullp, data, sizeof(long long) * size);
      break;
  }
  return dc;
}


void ks_datacont_delete(ks_datacont* dc)
{
  if (dc == NULL) return;
  if (dc->type < KS_CHARP)
    free(dc);
  else
  {
    free(dc->cp);
    free(dc);
  }
}


ks_datacont* ks_datacont_copy(const ks_datacont* dc)
{
  if (dc == NULL) return NULL;
  switch(dc->type)
  {
    case KS_CHAR:
      return ks_datacont_new(&(dc->c), dc->type, dc->size);
    case KS_SHORT:
      return ks_datacont_new(&(dc->s), dc->type, dc->size);
    case KS_INT:
      return ks_datacont_new(&(dc->i), dc->type, dc->size);
    case KS_LL:
      return ks_datacont_new(&(dc->ll), dc->type, dc->size);
    case KS_FLOAT:
      return ks_datacont_new(&(dc->f), dc->type, dc->size);
    case KS_DOUBLE:
      return ks_datacont_new(&(dc->d), dc->type, dc->size);
    case KS_UCHAR:
      return ks_datacont_new(&(dc->uc), dc->type, dc->size);
    case KS_USHORT:
      return ks_datacont_new(&(dc->us), dc->type, dc->size);
    case KS_UINT:
      return ks_datacont_new(&(dc->ui), dc->type, dc->size);
    case KS_ULL:
      return ks_datacont_new(&(dc->ull), dc->type, dc->size);
    case KS_CHARP:
      return ks_datacont_new(dc->cp, dc->type, dc->size);
    case KS_SHORTP:
      return ks_datacont_new(dc->sp, dc->type, dc->size);
    case KS_INTP:
      return ks_datacont_new(dc->ip, dc->type, dc->size);
    case KS_FLOATP:
      return ks_datacont_new(dc->fp, dc->type, dc->size);
    case KS_DOUBLEP:
      return ks_datacont_new(dc->dp, dc->type, dc->size);
    case KS_UCHARP:
      return ks_datacont_new(dc->ucp, dc->type, dc->size);
    case KS_USHORTP:
      return ks_datacont_new(dc->usp, dc->type, dc->size);
    case KS_UINTP:
      return ks_datacont_new(dc->uip, dc->type, dc->size);
    case KS_ULLP:
      return ks_datacont_new(dc->ullp, dc->type, dc->size);
  }
  return NULL;
}


static enum ks_comparison _compare_single_items(const ks_datacont* dca, const ks_datacont* dcb)
{
  switch(dca->type)
  {
    case KS_CHAR:
      if (dca->c == dcb->c) return KS_EQUAL;
      else if (dca->c < dcb->c) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
    case KS_SHORT:
      if (dca->s == dcb->s) return KS_EQUAL;
      else if (dca->s < dcb->s) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_INT:
      if (dca->i == dcb->i) return KS_EQUAL;
      else if (dca->i < dcb->i) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_LL:
      if (dca->ll == dcb->ll) return KS_EQUAL;
      else if (dca->ll < dcb->ll) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_FLOAT:
      if (dca->f == dcb->f) return KS_EQUAL;
      else if (dca->f < dcb->f) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_DOUBLE:
      if (dca->d == dcb->d) return KS_EQUAL;
      else if (dca->d < dcb->d) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_UCHAR:
      if (dca->uc == dcb->uc) return KS_EQUAL;
      else if (dca->uc < dcb->uc) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_USHORT:
      if (dca->us == dcb->us) return KS_EQUAL;
      else if (dca->us < dcb->us) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_UINT:
      if (dca->ui == dcb->ui) return KS_EQUAL;
      else if (dca->ui < dcb->ui) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
    case KS_ULL:
      if (dca->ull == dcb->ull) return KS_EQUAL;
      else if (dca->ull < dcb->ull) return KS_LESSTHAN;
      else return KS_GREATERTHAN;
      break;
  }
  return KS_CANTCOMPARE;
}


static enum ks_comparison _compare_multi_items(const ks_datacont* dca, const ks_datacont* dcb)
{
  switch(dca->type)
  {
    case KS_CHARP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->cp[i] < dcb->cp[i]) return KS_LESSTHAN;
	else if (dca->cp[i] > dcb->cp[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_SHORTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->sp[i] < dcb->sp[i]) return KS_LESSTHAN;
	else if (dca->sp[i] > dcb->sp[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_INTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->ip[i] < dcb->ip[i]) return KS_LESSTHAN;
	else if (dca->ip[i] > dcb->ip[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_LLP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->llp[i] < dcb->llp[i]) return KS_LESSTHAN;
	else if (dca->llp[i] > dcb->llp[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_FLOATP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->fp[i] < dcb->fp[i]) return KS_LESSTHAN;
	else if (dca->fp[i] > dcb->fp[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_DOUBLEP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->dp[i] < dcb->dp[i]) return KS_LESSTHAN;
	else if (dca->dp[i] > dcb->dp[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_UCHARP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->ucp[i] < dcb->ucp[i]) return KS_LESSTHAN;
	else if (dca->ucp[i] > dcb->ucp[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_USHORTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->usp[i] < dcb->usp[i]) return KS_LESSTHAN;
	else if (dca->usp[i] > dcb->usp[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_UINTP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->uip[i] < dcb->uip[i]) return KS_LESSTHAN;
	else if (dca->uip[i] > dcb->uip[i]) return KS_GREATERTHAN;
      }
      break;
    case KS_ULLP:
      for (int i = 0; i < dca->size && i < dcb->size; i++)
      {
        if (dca->ullp[i] < dcb->ullp[i]) return KS_LESSTHAN;
	else if (dca->ullp[i] > dcb->ullp[i]) return KS_GREATERTHAN;
      }
      break;
  }
  if (dca->size < dcb->size) return KS_LESSTHAN;
  else if (dca->size > dcb->size) return KS_GREATERTHAN;
  else return KS_EQUAL;
}


enum ks_comparison ks_datacont_compare(const ks_datacont* dca, const ks_datacont* dcb)
{
  if (dca->type != dcb->type)
    return KS_CANTCOMPARE;

  if (dca->type < KS_CHARP)
    return _compare_single_items(dca, dcb);
  else return _compare_multi_items(dca, dcb);
}


static uint32_t __hash(const void* data, const size_t size)
{
  uint32_t hash = 5381;

  for (int i = 0; i < size; i++)
  {
    uint8_t byte = *((uint8_t *) data + i);
    hash = ((hash << 5) + hash) + byte;
  }

  return hash;
}


uint32_t ks_datacont_hash(const ks_datacont* dc)
{
  switch(dc->type)
  {
    case KS_CHAR:
    case KS_UCHAR:
      return __hash(&dc->c, sizeof(char));
    case KS_SHORT:
    case KS_USHORT:
      return __hash(&dc->s, sizeof(short));
    case KS_INT:
    case KS_UINT:
      return __hash(&dc->i, sizeof(int));
    case KS_LL:
    case KS_ULL:
      return __hash(&dc->ll, sizeof(long long));
    case KS_FLOAT:
      return __hash(&dc->f, sizeof(float));
    case KS_DOUBLE:
      return __hash(&dc->d, sizeof(double));
    case KS_CHARP:
      return __hash(dc->cp, sizeof(char) * dc->size);
    case KS_SHORTP:
      return __hash(dc->sp, sizeof(short) * dc->size);
    case KS_INTP:
      return __hash(dc->ip, sizeof(int) * dc->size);
    case KS_LLP:
      return __hash(dc->llp, sizeof(long long) * dc->size);
    case KS_FLOATP:
      return __hash(dc->fp, sizeof(float) * dc->size);
    case KS_DOUBLEP:
      return __hash(dc->dp, sizeof(double) * dc->size);
  }
}
