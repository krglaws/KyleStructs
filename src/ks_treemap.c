#include "kylestructs/ks_treemap.h"

#include <stdlib.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_list.h"
#include "kylestructs/ks_listnode.h"
#include "kylestructs/ks_treemapnode.h"
#include "kylestructs/ks_types.h"

ks_treemap* ks_treemap_new() { return calloc(1, sizeof(ks_treemap)); }

void ks_treemap_delete(ks_treemap* tm) {
    if (tm == NULL) return;

    ks_treemapnode_delete_all(tm->root);

    free(tm);
}

ks_treemap* ks_treemap_copy(const ks_treemap* tm) {
    if (tm == NULL) return NULL;

    ks_treemap* tm_copy = ks_treemap_new();

    tm_copy->root = ks_treemapnode_copy_all(tm->root);

    return tm_copy;
}

int ks_treemap_add(ks_treemap* tm, const ks_datacont* key,
                   const ks_datacont* value) {
    if (tm == NULL || key == NULL || value == NULL) return -1;

    if (tm->root == NULL) {
        tm->root = ks_treemapnode_new(key, value);
        return 0;
    }
    return ks_treemapnode_add(tm->root, key, value);
}

int ks_treemap_remove(ks_treemap* tm, const ks_datacont* key) {
    if (tm == NULL) return -1;

    return ks_treemapnode_remove(&tm->root, key);
}

const ks_datacont* ks_treemap_get(const ks_treemap* tm,
                                  const ks_datacont* key) {
    if (tm == NULL) return NULL;

    return ks_treemapnode_get(tm->root, key);
}

const ks_datacont* ks_treemap_get_key(const ks_treemap* tm, int index) {
    if (tm == NULL) return NULL;

    return ks_treemapnode_get_key(tm->root, index);
}

unsigned int ks_treemap_count(const ks_treemap* tm) {
    if (tm == NULL) return 0;

    return ks_treemapnode_count(tm->root);
}

unsigned int ks_treemap_height(const ks_treemap* tm) {
    if (tm == NULL) return 0;

    return ks_treemapnode_height(tm->root);
}

void ks_treemap_balance(ks_treemap* tm) {
    if (tm == NULL) return;

    tm->root = ks_treemapnode_balance(tm->root);
}
