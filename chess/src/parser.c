#include <stdio.h>

#include "parser.h"
#include "new.h"

#include "chessmen/king.h"
#include "chessmen/queen.h"
#include "chessmen/rook.h"
#include "chessmen/bishop.h"
#include "chessmen/knight.h"
#include <string.h>

#define BUFF_SIZE 32
const char* KING = "king";
const char* QUEEN = "queen";
const char* ROOK = "rook";
const char* BISHOP = "bishop";
const char* KNIGHT = "knight";


static struct Chessman* parse_chessman(const char* str) {
    if (!str) return NULL;

    char objName[BUFF_SIZE];
    int x, y;
    int num = sscanf(str, "%s %d %d", objName, &x, &y);
    x = x - 1;
    y = y - 1;
    objName[BUFF_SIZE - 1] = '\0';

    if (num == -1) return NULL;
    else if (!strcmp(objName, KING)) {
        return new(King, x, y);
    }
    else if (!strcmp(objName, QUEEN)) {
        return new(Queen, x, y);
    }
    else if (!strcmp(objName, ROOK)) {
        return new(Rook, x, y);
    }
    else if (!strcmp(objName, BISHOP)) {
        return new(Bishop, x, y);
    }
    else if (!strcmp(objName, KNIGHT)) {
        return new(Knight, x, y);
    }
    else {
        printf("Incorrect param count in str: %s\n", str);
        return NULL;
    }
}

struct Chessman* parse_data(const char* file_name) {
    FILE* F = fopen(file_name, "r");
    if (F == NULL) {
        printf("Can't open!");
        return NULL;
    }

    struct Chessman* chessmen = slist_create(sizeof(struct Chessman*));
    size_t cur = slist_stop(chessmen);
    char str[BUFF_SIZE];
    while (fgets(str, BUFF_SIZE, F)) {
        void* chessman = parse_chessman(str);
        if (chessman != NULL)
        {
            void** cr = (void**)slist_insert(chessmen, cur);
            *cr = chessman;
            if (slist_count(chessmen) == 1)
            {
                cur = slist_first(chessmen);
            }
            else
            {
                cur = slist_next(chessmen, cur);
            }
        }
    }
    fclose(F);
    return chessmen;
}

void delete_data(struct Chessman* _slist) {
    slist_destroy(_slist, NULL);
}