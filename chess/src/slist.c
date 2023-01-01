#include "slist.h"

#include <stdlib.h>
#define STOP (size_t)NULL

typedef struct Node {
    void* value;
    struct Node* next;
} Node;

typedef struct SList {
    Node* head;
    size_t length;
    size_t  itemSize;
} SList;

void* slist_create(size_t itemSize) {
    if (itemSize == 0) {
        return NULL;
    }
    SList* slist = (SList*)(malloc(sizeof(SList)));
    if (slist == NULL) {
        return NULL;
    }
    slist->head = NULL;
    slist->length = 0;
    slist->itemSize = itemSize;
    return slist;
}

void slist_destroy(void* slist, void(*destroy)(void*)) {
    if (slist != NULL) {
        slist_clear(slist, destroy);
    }
    free(slist);
}

void* slist_init(void* slist, size_t itemSize, void(*destroy)(void*)) {
    if (itemSize == 0) {
        return NULL;
    }
    if (slist != NULL) {
        slist_clear(slist, destroy);
        ((SList*)slist)->itemSize = itemSize;
    }
    return slist;
}

void slist_clear(void* slist, void(*destroy)(void*)) {
    if (slist != NULL) {
        while (((SList*)slist)->length > 0) {
            slist_remove(slist, destroy);
        }
    }
}

size_t slist_count(const void* slist) {
    if (slist == NULL) {
        return INVALID;
    }
    const SList* current_slist = (SList*)slist;
    return current_slist->length;
}

void* slist_item(void* slist, size_t i) {
    if (slist == NULL) {
        return NULL;
    }
    SList* current_slist = (SList*)slist;
    if (current_slist->length <= i) {
        return NULL;
    }
    if (current_slist->head == NULL) {
        return NULL;
    }
    Node* node = current_slist->head;
    while (i--) {
        node = node->next;
    }
    return node->value;
}

static Node* node_create(SList* slist) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }
    node->value = malloc(slist->itemSize);
    if (node->value == NULL) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

void* slist_prepend(void* slist) {
    slist_insert(slist, STOP);
    return ((Node*)slist_first(slist))->value;
}

void slist_remove(void* slist, void(*destroy)(void*)) {
    slist_erase(slist, (size_t)((SList*)slist)->head, destroy);
}

size_t slist_first(const void* slist) {
    SList* current_slist = (SList*)slist;
    if (current_slist == NULL) {
        return STOP;
    }
    return (size_t)current_slist->head;
}

size_t slist_next(const void* slist, size_t item_id) {
    SList* current_slist = (SList*)slist;
    if (current_slist == NULL || item_id == STOP) {
        return STOP;
    }
    Node* node = (void*)item_id;
    return (size_t)node->next;
}

size_t slist_stop(const void* slist) {
    return STOP;
}

void* slist_current(const void* slist, size_t item_id) {
    if (slist == NULL || item_id == STOP) {
        return NULL;
    }
    return ((Node*)item_id)->value;
}

void* slist_insert(void* slist, size_t item_id) {
    if (slist == NULL) {
        return NULL;
    }
    SList* current_slist = (SList*)slist;
    if (current_slist->head == NULL && item_id == STOP) {
        current_slist->head = node_create(current_slist);
        if (current_slist->head == NULL) {
            return NULL;
        }
        current_slist->length++;
        return current_slist->head->value;
    }
    if (current_slist->head != NULL && item_id == STOP) {
        Node* node = node_create(current_slist);
        if (node == NULL) {
            return NULL;
        }
        node->next = current_slist->head;
        current_slist->head = node;
        current_slist->length++;
        return node->value;
    }
    if (current_slist->head != NULL && item_id != STOP) {
        Node* node = (Node*)item_id;
        Node* new_node = node_create(current_slist);
        if (node->next == NULL) {
            node->next = new_node;
            current_slist->length++;
            return new_node->value;
        }
        if (node->next != NULL) {
            new_node->next = node->next;
            node->next = new_node;
            current_slist->length++;
            return new_node->value;
        }
    }
    return NULL;
}

static Node* find_prev(SList* slist, Node* node) {
    if (slist->head == NULL || slist->head == node) {
        return NULL;
    }
    for (Node* prev_node = slist->head; prev_node->next != NULL; prev_node = prev_node->next) {
        if (prev_node->next == node) {
            return prev_node;
        }
    }
    return NULL;
}

void slist_erase(void* slist, size_t item_id, void(*destroy)(void*)) {
    if (slist == NULL || item_id == STOP) { return; }
    SList* current_slist = (SList*)slist;
    if (current_slist->head == NULL) { return; }
    Node* node = (Node*)item_id;
    if (node == current_slist->head) {
        if (node->value != NULL) {
            if (destroy != NULL)
                destroy(node->value);
            free(node->value);
        }

        current_slist->head = node->next;
        current_slist->length--;

        free(node);
        return;
    }
    Node* prev_node = find_prev(current_slist, node);
    prev_node->next = node->next;
    if (destroy != NULL) {
        destroy(node->value);
    }
    free(node->value);
    free(node);
    current_slist->length--;
}
