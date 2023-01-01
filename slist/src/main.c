#include <assert.h>

#include "slist.h"

static size_t STOP = (size_t)NULL;

typedef struct {
    int array[8];
    float d_variable;
} Value;

int main()
{
    assert(slist_create(0) == NULL);

    slist_destroy(NULL, NULL);

    assert(slist_init(NULL, sizeof(Value), NULL) == NULL);

    slist_clear(NULL, NULL);

    assert(slist_count(NULL) == INVALID);

    assert(slist_item(NULL, 0) == NULL);
    assert(slist_item(NULL, -1) == NULL);
    assert(slist_item(NULL, 1) == NULL);

    assert(slist_prepend(NULL) == NULL);

    slist_remove(NULL, NULL);

    assert(slist_stop(NULL) == STOP);

    assert(slist_stop(NULL) == slist_first(NULL));

    assert(slist_current(NULL, slist_count(NULL)) == NULL);
    assert(slist_next(NULL, slist_count(NULL)) == slist_stop(NULL));

    for (size_t i = slist_first(NULL); i != slist_stop(NULL); i = slist_next(NULL, i)) {}

    assert(slist_insert(NULL, slist_stop(NULL)) == NULL);

    slist_erase(NULL, slist_stop(NULL), NULL);

    void* slist = slist_create(sizeof(Value));
    assert(slist != NULL);
    assert(0 == slist_count(slist));
    assert(slist_stop(slist) == slist_first(slist));
    slist_destroy(slist, NULL);

    slist = slist_create(sizeof(Value));
    slist_clear(slist, NULL);
    assert(slist_count(slist) == 0);

    assert(slist_item(slist, 0) == NULL);
    assert(slist_item(slist, -1) == NULL);
    assert(slist_item(slist, 1) == NULL);

    void* E = slist_prepend(slist);
    assert(E != NULL);
    assert(slist_count(slist) == 1);
    assert(slist_item(slist, 0) == E);

    slist_remove(slist, NULL);
    assert(slist_count(slist) == 0);

    assert(slist_first(slist) == slist_stop(slist));

    E = slist_insert(slist, slist_stop(slist));
    assert(E != NULL);
    assert(slist_count(slist) == 1);
    assert(slist_item(slist, 0) == E);
    slist_erase(slist, slist_stop(slist), NULL);

    assert(E == slist_item(slist, 0));

    E = slist_prepend(slist);
    assert(E != NULL);
    assert(slist_count(slist) == 2);
    assert(slist_item(slist, 0) == E);
    assert(slist_item(slist, 1) != E);
    assert(slist_first(slist) != slist_stop(slist));

    E = slist_current(slist, slist_first(slist));
    assert(E != NULL);
    assert(slist_current(slist, slist_stop(slist)) == NULL);

    slist_remove(slist, NULL);
    assert(slist_count(slist) == 1);
    assert(slist_next(slist, slist_first(slist)) == slist_stop(slist));

    E = slist_insert(slist, slist_first(slist));
    assert(E != NULL);
    assert(slist_count(slist) == 2);
    assert(slist_item(slist, 0) != E);
    assert(slist_item(slist, 1) == E);
    slist_clear(slist, NULL);

    slist_insert(slist, slist_first(slist));
    E = slist_insert(slist, slist_stop(slist));
    assert(E == NULL);
    assert(slist_count(slist) == 1);

    return 0;
}