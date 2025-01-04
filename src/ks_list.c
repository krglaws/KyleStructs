#include "kylestructs/ks_list.h"

#include <stdlib.h>

#include "kylestructs/ks_datacont.h"
#include "kylestructs/ks_listnode.h"
#include "kylestructs/ks_types.h"

ks_list* ks_list_new() { return calloc(1, sizeof(ks_list)); }

void ks_list_delete(ks_list* ls) {
    if (ls == NULL) return;

    ks_listnode_delete_all(ls->head);

    free(ls);
}

ks_list* ks_list_copy(const ks_list* ls) {
    if (ls == NULL) return NULL;

    ks_list* ls_copy = ks_list_new();

    ls_copy->head = ks_listnode_copy_all(ls->head);

    return ls_copy;
}

int ks_list_add(ks_list* ls, const ks_datacont* dc) {
    if (ls == NULL || dc == NULL) return -1;

    if (ls->head) return ks_listnode_add(ls->head, dc);

    ls->head = ks_listnode_new(dc);

    return 0;
}

ks_list* ks_list_merge(ks_list* lsa, ks_list* lsb) {
    if (lsa == NULL || lsb == NULL) return lsa ? lsa : lsb;

    lsa->head = ks_listnode_merge(lsa->head, lsb->head);

    free(lsb);

    return lsa;
}

int ks_list_remove_by(ks_list* ls, const ks_datacont* dc) {
    if (ls == NULL || dc == NULL) return -1;

    return ks_listnode_remove_by(&(ls->head), dc);
}

int ks_list_remove_at(ks_list* ls, int index) {
    if (ls == NULL) return -1;

    return ks_listnode_remove_at(&(ls->head), index);
}

int ks_list_remove_all(ks_list* ls, const ks_datacont* dc) {
    if (ls == NULL || dc == NULL) return -1;

    return ks_listnode_remove_all(&(ls->head), dc);
}

int ks_list_replace_by(ks_list* ls, const ks_datacont* old_dc,
                       const ks_datacont* new_dc) {
    if (ls == NULL || old_dc == NULL || new_dc == NULL) return -1;

    return ks_listnode_replace_by(ls->head, old_dc, new_dc);
}

int ks_list_replace_at(ks_list* ls, const ks_datacont* dc, int index) {
    if (ls == NULL || dc == NULL) return -1;

    return ks_listnode_replace_at(ls->head, dc, index);
}

int ks_list_replace_all(ks_list* ls, const ks_datacont* old_dc,
                        const ks_datacont* new_dc) {
    if (ls == NULL || old_dc == NULL || new_dc == NULL) return -1;

    return ks_listnode_replace_all(ls->head, old_dc, new_dc);
}

int ks_list_insert(ks_list* ls, const ks_datacont* dc, int index) {
    if (ls == NULL || dc == NULL) return -1;

    return ks_listnode_insert(&(ls->head), dc, index);
}

int ks_list_push(ks_list* ls, const ks_datacont* dc) {
    if (ls == NULL || dc == NULL) return -1;

    if (ls->head != NULL) return ks_listnode_insert(&(ls->head), dc, 0);

    ls->head = ks_listnode_new(dc);

    return 0;
}

ks_datacont* ks_list_pop(ks_list* ls) {
    if (ls == NULL || ls->head == NULL) return NULL;

    ks_datacont* dc = ks_datacont_copy(ks_listnode_get(ls->head, 0));

    ks_listnode_remove_at(&(ls->head), 0);

    return dc;
}

const ks_datacont* ks_list_peek(const ks_list* ls) {
    if (ls == NULL) return NULL;

    return ks_listnode_get(ls->head, 0);
}

int ks_list_enqueue(ks_list* ls, const ks_datacont* dc) {
    if (ls == NULL || dc == NULL) return -1;

    return ks_listnode_insert(&(ls->head), dc, 0);
}

ks_datacont* ks_list_dequeue(ks_list* ls) {
    if (ls == NULL || ls->head == NULL) return NULL;

    ks_datacont* dc = ks_datacont_copy(ks_listnode_get(ls->head, -1));

    ks_listnode_remove_at(&(ls->head), -1);

    return dc;
}

int ks_list_index(const ks_list* ls, const ks_datacont* dc) {
    if (ls == NULL || dc == NULL) return -1;

    return ks_listnode_index(ls->head, dc);
}

const ks_datacont* ks_list_get(const ks_list* ls, int index) {
    if (ls == NULL) return NULL;

    return ks_listnode_get(ls->head, index);
}

unsigned int ks_list_count(const ks_list* ls, const ks_datacont* dc) {
    if (ls == NULL || dc == NULL) return -1;

    return ks_listnode_count(ls->head, dc);
}

unsigned int ks_list_length(const ks_list* ls) {
    if (ls == NULL) return 0;

    return ks_listnode_length(ls->head);
}
