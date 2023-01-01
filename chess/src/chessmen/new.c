#include <stdlib.h>
#include <assert.h>

#include "new.h"

void* new(const void* _class, ...)
{
    const struct Class* class = _class;

    void* p = calloc(1, class->size);

    assert(p);

    *(const struct Class**)p = class;

    if (class->ctor)
    {
        va_list ap;

        va_start(ap, _class);

        p = class->ctor(p, &ap);

        va_end(ap);
    }

    return p;
}

void delete(void* self)
{
    const struct Class** cp = self;

    if (self && *cp && (*cp)->dtor) {
        self = (*cp)->dtor(self);
    }

    free(self);
}

void check_attack(const void* self, void* board)
{
    const struct Class* const* ptr = NULL;
    if (self)
    {
        ptr = (const struct Class* const*)self;
        if (*ptr && (*ptr)->check_attack)
        {
            (*ptr)->check_attack(self, board);
        }
    }
}
