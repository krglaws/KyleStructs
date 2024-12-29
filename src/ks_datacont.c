#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include <ks_types.h>
#include <ks_datacont.h>
#include <ks_listnode.h>
#include <ks_list.h>
#include <ks_treesetnode.h>
#include <ks_treeset.h>
#include <ks_hashset.h>
#include <ks_treemapnode.h>
#include <ks_treemap.h>
#include <ks_hashmap.h>


ks_datacont* ks_datacont_new(const void* data, const enum ks_datatype dct, const size_t size)
{
  if (data == NULL)
  {
     return NULL;
  }

  if (size == 0 && dct != KS_CHARP)
  {
    return NULL;
  }

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
    case KS_VOIDP:
      dc->vp = (void*) data;
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
    case KS_LIST:
      dc->ls = (ks_list*) data;
      break;
    case KS_TREESET:
      dc->ts = (ks_treeset*) data;
      break;
    case KS_HASHSET:
      dc->hs = (ks_hashset*) data;
      break;
    case KS_TREEMAP:
      dc->tm = (ks_treemap*) data;
      break;
    case KS_HASHMAP:
      dc->hm = (ks_hashmap*) data;
      break;
  }
  return dc;
}


void ks_datacont_delete(ks_datacont* dc)
{
  if (dc == NULL)
  {
    return;
  }

  if (dc->type > KS_ULLP)
  {
    switch (dc->type)
    {
      case KS_CHAR:
      case KS_SHORT:
      case KS_INT:
      case KS_LL:
      case KS_FLOAT:
      case KS_DOUBLE:
      case KS_UCHAR:
      case KS_USHORT:
      case KS_UINT:
      case KS_ULL:
      case KS_VOIDP:
        /* do nothing
         * (VOIDP might point to a custom data structure)
         */
        break;
      case KS_CHARP:
      case KS_SHORTP:
      case KS_INTP:
      case KS_LLP:
      case KS_FLOATP:
      case KS_DOUBLEP:
      case KS_UCHARP:
      case KS_USHORTP:
      case KS_UINTP:
      case KS_ULLP:
        free(dc->cp);
        break;
      case KS_LIST:
        ks_list_delete(dc->ls);
        break;
      case KS_TREESET:
        ks_treeset_delete(dc->ts);
        break;
      case KS_HASHSET:
        ks_hashset_delete(dc->hs);
        break;
      case KS_TREEMAP:
        ks_treemap_delete(dc->tm);
        break;
      case KS_HASHMAP:
        ks_hashmap_delete(dc->hm);
        break;
    }
  }

  free(dc);
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
    case KS_VOIDP:
      return ks_datacont_new(&(dc->vp), dc->type, dc->size);
    case KS_CHARP:
      return ks_datacont_new(dc->cp, dc->type, dc->size);
    case KS_SHORTP:
      return ks_datacont_new(dc->sp, dc->type, dc->size);
    case KS_INTP:
      return ks_datacont_new(dc->ip, dc->type, dc->size);
    case KS_LLP:
      return ks_datacont_new(dc->llp, dc->type, dc->size);
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
    case KS_LIST:
      return ks_datacont_new(ks_list_copy(dc->ls), dc->type, dc->size);
    case KS_TREESET:
      return ks_datacont_new(ks_treeset_copy(dc->ts), dc->type, dc->size);
    case KS_HASHSET:
      return ks_datacont_new(ks_hashset_copy(dc->hs), dc->type, dc->size);
    case KS_TREEMAP:
      return ks_datacont_new(ks_treemap_copy(dc->tm), dc->type, dc->size);
    case KS_HASHMAP:
      return ks_datacont_new(ks_hashmap_copy(dc->hm), dc->type, dc->size);
  }
  return NULL;
}


enum ks_comparison ks_datacont_compare(const ks_datacont* dca, const ks_datacont* dcb)
{
  if (dca == NULL || dcb == NULL || dca->type != dcb->type)
  {
    return KS_CANTCOMPARE;
  }

  switch(dca->type)
  {
    case KS_CHAR:
      if (dca->c == dcb->c) return KS_EQUAL;
      if (dca->c < dcb->c) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_SHORT:
      if (dca->s == dcb->s) return KS_EQUAL;
      if (dca->s < dcb->s) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_INT:
      if (dca->i == dcb->i) return KS_EQUAL;
      if (dca->i < dcb->i) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_LL:
      if (dca->ll == dcb->ll) return KS_EQUAL;
      if (dca->ll < dcb->ll) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_FLOAT:
      if (dca->f == dcb->f) return KS_EQUAL;
      if (dca->f < dcb->f) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_DOUBLE:
      if (dca->d == dcb->d) return KS_EQUAL;
      if (dca->d < dcb->d) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_UCHAR:
      if (dca->uc == dcb->uc) return KS_EQUAL;
      if (dca->uc < dcb->uc) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_USHORT:
      if (dca->us == dcb->us) return KS_EQUAL;
      if (dca->us < dcb->us) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_UINT:
      if (dca->ui == dcb->ui) return KS_EQUAL;
      if (dca->ui < dcb->ui) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_ULL:
      if (dca->ull == dcb->ull) return KS_EQUAL;
      if (dca->ull < dcb->ull) return KS_LESSTHAN;
      return KS_GREATERTHAN;
    case KS_VOIDP:
    case KS_CHARP:
    case KS_SHORTP:
    case KS_INTP:
    case KS_LLP:
    case KS_FLOATP:
    case KS_DOUBLEP:
    case KS_UCHARP:
    case KS_USHORTP:
    case KS_UINTP:
    case KS_ULLP:
    case KS_LIST:
    case KS_TREESET:
    case KS_HASHSET:
    case KS_TREEMAP:
    case KS_HASHMAP:
      if (dca->vp == dcb->vp) return KS_EQUAL;
      if (dca->vp < dcb->vp) return KS_LESSTHAN;
      return KS_GREATERTHAN;
      break;
  }

  if (dca->size < dcb->size) return KS_LESSTHAN;
  if (dca->size > dcb->size) return KS_GREATERTHAN;

  return KS_EQUAL;
}


static uint32_t __hash(const void* data, const size_t size)
{
  uint32_t hash = 5381;

  for (size_t i = 0; i < size; i++)
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
    case KS_SHORTP:
    case KS_INTP:
    case KS_LLP:
    case KS_FLOATP:
    case KS_DOUBLEP:
    case KS_UCHARP:
    case KS_USHORTP:
    case KS_UINTP:
    case KS_ULLP:
      return __hash(dc->cp, dc->size);
    default:
      return __hash(&dc->vp, sizeof(void *));
  }
}
