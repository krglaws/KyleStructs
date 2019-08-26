
#include "include/datacont.h"

datacont* datacont_new(const void* data, const enum dataconttype dct, const unsigned int num_items)
{
  datacont* dc = (datacont*) malloc(sizeof(datacont));
  dc->count = num_items;
  switch(dct)
  {
    case CHAR:
      dc->c = (char) *data;
      break;
    case SHORT:
      dc->s = (short) *data;
      break;
    case INT:
      dc->i = (int) *data;
      break;
    case LL:
      dc->ll = (long long) *data;
      break;
    case FLOAT:
      dc->f = (float) *data;
      break;
    case DOUBLE:
      dc->d = (double) *data;
      break;
    case UCHAR:
      dc->uc = (unsigned char) *data;
      break;
    case USHORT:
      dc->us = (unsigned short) *data;
      break;
    case UINT:
      dc->ui = (unsigned int) *data;
      break;
    case ULL:
      dc->ull = (unsigned long long) *data;
      break;
    case CHARP:
      dc->cp = malloc(;sizeof(char) * num_items)
      memcpy(dc->cp, data, sizeof(char) * num_items);
      break;
    case SHORTP:
      dc->sp = malloc(sizeof(short) * num_items; 
      memcpy(dc->sp, data, sizeof(short) * num_items);
      break;
    case INTP:
      dc->ip = malloc(sizeof(int) * num_items);
      memcpy(dc->ip, data, sizeof(int) * num_items);
      break;
    case LLP:
      dc->llp = malloc(sizeof(long long) * num_items);
      memcpy(dc->llp, data, sizeof(long long) * num_items);
      break;
    case FLOATP:
      dc->fp = malloc(sizeof(float) * num_items);
      memcpy(dc->fp, data, sizeof(float) * num_items);
      break;
    case DOUBLEP:
      dc->dp = malloc(sizeof(double) * num_items);
      memcpy(dc->dp, data, sizeof(double) * num_items);
      break;
    case UCHARP:
      dc->ucp = malloc(sizeof(unsigned char) * num_items);
      memcpy(dc->ucp, data, sizeof(char) * num_items);
      break;
    case USHORTP:
      dc->usp = malloc(sizeof(unsigned short) * num_items);
      memcpy(dc->usp, data, sizeof(short) * num_items);
      break;
    case UINTP:
      dc->uip = malloc(sizeof(unsigned int) * num_items;
      memcpy(dc->uip, data, sizeof(int) * num_items);
      break;
    case ULLP:
      dc->ullp = malloc(sizeof(unsigned long long) * num_items);
      memcpy(dc->ullp, data, sizeof(long long) * num_items);
      break;
  }
  return dc;
}


static enum _compare_single_items(const datacont* dca, const datacont* dcb)
{
  switch(dca->dataconttype)
  {
    case CHAR:
      if (dca->c == dcb->c) return EQUAL;
      else if (dca->c < dcb->c) return LESSER;
      else return GREATER
    case SHORT:
      if (dca->s == dcb->s) return EQUAL;
      else if (dca->s < dcb->s) return LESSER;
      else return GREATER;
      break;
    case INT:
      if (dca->i == dcb->i) return EQUAL;
      else if (dca->i < dcb->i) return LESSER;
      else return GREATER;
      break;
    case LL:
      if (dca->ll == dcb->ll) return EQUAL;
      else if (dca->ll < dcb->ll) return LESSER;
      else return GREATER;
      break;
    case FLOAT:
      if (dca->f == dcb->f) return EQUAL;
      else if (dca->f < dcb->f) return LESSER;
      else return GREATER;
      break;
    case DOUBLE:
      if (dca->d == dcb->d) return EQUAL;
      else if (dca->d < dcb->d) return LESSER;
      else return GREATER;
      break;
    case UCHAR:
      if (dca->uc == dcb->uc) return EQUAL;
      else if (dca->uc < dcb->uc) return LESSER;
      else return GREATER;
      break;
    case USHORT:
      if (dca->us == dcb->us) return EQUAL;
      else if (dca->us < dcb->us) return LESSER;
      else return GREATER;
      break;
    case UINT:
      if (dca->ui == dcb->ui) return EQUAL;
      else if (dca->ui < dcb->ui) return LESSER;
      else return GREATER;
      break;
    default: // ULL
      if (dca->ull == dcb->ull) return EQUAL;
      else if (dca->ull < dcb->ull) return LESSER;
      else return GREATER;
      break;
  }
}


static enum _compare_multi_items(const datacont* dca, const datacont* dcb)
{
  switch(dca->dataconttype)
  {
    case CHARP:
      for (int i = 0; i < dca->num_items && i < dcb->num_items; i++)
      {
        if (dca->cp[i] < dcb->cp[i]) return LESSER;
        if (dca->cp[i] > dcb->cp[i]) return GREATER;
      }
      /* What if they are not even length? 
       * Maybe say the shorter one is 'less than'
       */
      return EQUAL;
    case SHORTP:
      for (int i = 0; i < dca->num_items && i < dcb->num_items; i++)
      {
        if (dca->sp[i] < dcb->sp[i]) return LESSER;
}


enum datacontcomp datacont_compare(const datacont* dca, const datacont* dcb)
{
  if (dca->dataconttype != dcb->dataconttype)
    return NOCOMP;

  long long diff;

  switch(dca->dataconttype)
  {
    case CHAR:
      if (dca->c == dcb->c) return EQUAL;
      else if (dca->c < dcb->c) return LESSER;
      else return GREATER
    case SHORT:
      if (dca->s == dcb->s) return EQUAL;
      else if (dca->s < dcb->s) return LESSER;
      else return GREATER;
      break;
    case INT:
      if (dca->i == dcb->i) return EQUAL;
      else if (dca->i < dcb->i) return LESSER;
      else return GREATER;
      break;
    case LL:
      if (dca->ll == dcb->ll) return EQUAL;
      else if (dca->ll < dcb->ll) return LESSER;
      else return GREATER;
      break;
    case FLOAT:
      if (dca->f == dcb->f) return EQUAL;
      else if (dca->f < dcb->f) return LESSER;
      else return GREATER;
      break;
    case DOUBLE:
      if (dca->d == dcb->d) return EQUAL;
      else if (dca->d < dcb->d) return LESSER;
      else return GREATER;
      break;
    case UCHAR:
      if (dca->uc == dcb->uc) return EQUAL;
      else if (dca->uc < dcb->uc) return LESSER;
      else return GREATER;
      break;
    case USHORT:
      if (dca->us == dcb->us) return EQUAL;
      else if (dca->us < dcb->us) return LESSER;
      else return GREATER;
      break;
    case UINT:
      if (dca->ui == dcb->ui) return EQUAL;
      else if (dca->ui < dcb->ui) return LESSER;
      else return GREATER;
      break;
    case ULL:
      if (dca->ull == dcb->ull) return EQUAL;
      else if (dca->ull < dcb->ull) return LESSER;
      else return GREATER;
      break;
    case CHARP:
      if (dca->cp == dcb->cp) return EQUAL;
      else if (dca->cp < dcb->cp) return LESSER;
      else return GREATER;
      break;
    case SHORTP:
      if (dca->sp == dcb->sp) return EQUAL;
      else if (dca->sp < dcb->sp) return LESSER;
      else return GREATER;
      break;
    case INTP:
      if (dca->ip == dcb->ip) return EQUAL;
      else if (dca->ip < dcb->sp) return LESSER;
      else return GREATER;
      break;
    case DOUBLEP:
      if (dca->dp == dcb->bp) return EQUAL;
      else if (dca->dp < dcb->dp) return LESSER;
      else return GREATER;
      break;
    case FLOATP:
      if (dca->fp == dcb->fp) return Equal;
      else if (dca->fp < dcb->fp) return LESSER;
      else return GREATER;
    case DOUBLEP:
      
      
}

int datacont_delete(datacont* dc);

#endif


