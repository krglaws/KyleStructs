#include "kylestructs/ks_iterator.h"

#include <stdlib.h>

#include "kylestructs/ks_hashmap.h"
#include "kylestructs/ks_hashset.h"
#include "kylestructs/ks_list.h"
#include "kylestructs/ks_treemap.h"
#include "kylestructs/ks_treeset.h"
#include "kylestructs/ks_types.h"

ks_iterator* ks_iterator_new(const void* ks_obj, enum ks_datatype type) {
  if (ks_obj == NULL) {
    return NULL;
  }

  ks_iterator* iter = calloc(1, sizeof(ks_iterator));
  iter->parent = (void*)ks_obj;
  iter->type = type;

  switch (type) {
    case KS_LIST:
      iter->size = ks_list_length(ks_obj);
      iter->curr = ((ks_list*)ks_obj)->head;
      break;

    case KS_TREESET:
      iter->size = ks_treeset_count(ks_obj);
      break;

    case KS_HASHSET:
      iter->size = ks_hashset_count(ks_obj);
      break;

    case KS_TREEMAP:
      iter->size = ks_treemap_count(ks_obj);
      break;

    case KS_HASHMAP:
      iter->size = ks_hashmap_count(ks_obj);
      break;

    default:
      free(iter);
      iter = NULL;
  }

  return iter;
}

void ks_iterator_delete(ks_iterator* iter) { free(iter); }

const ks_datacont* ks_iterator_next(ks_iterator* iter) {
  if (iter == NULL) {
    return NULL;
  }

  const ks_datacont* dc;

  switch (iter->type) {
    case KS_LIST:
      dc = iter->curr ? iter->curr->dc : NULL;
      iter->index += 1;
      iter->curr = iter->curr ? iter->curr->next : NULL;
      break;

    case KS_TREESET:
      dc = ks_treeset_get((ks_treeset*)iter->parent, iter->index);
      iter->index += 1;
      break;

    case KS_HASHSET:
      dc = ks_hashset_get((ks_hashset*)iter->parent, iter->index);
      iter->index += 1;
      break;

    case KS_TREEMAP:
      dc = ks_treemap_get_key((ks_treemap*)iter->parent, iter->index);
      iter->index += 1;
      break;

    case KS_HASHMAP:
      dc = ks_hashmap_get_key((ks_hashmap*)iter->parent, iter->index);
      iter->index += 1;
      break;
    default:
      dc = NULL;
  }

  return dc;
}
