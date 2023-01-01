#include "chessman.h"
#include <stdarg.h>

static void* Chessman_ctor(void* _self, va_list* app)
{
    struct Chessman* self = NULL;
    if (_self)
    {
        self = (struct Chessman*)_self;
        self->x = va_arg(*app, int);
        self->y = va_arg(*app, int);
    }
    return self;
}

static const struct Class _Chessman = {
        sizeof(struct Chessman),
        Chessman_ctor,
        NULL,
        NULL
};

const void* Chessman = &_Chessman;
