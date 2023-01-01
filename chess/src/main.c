#include "parser.h"
#include "chessmen/chessman.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
    const char* file_name = "src/test.txt";
    Board board;
    void* chessmen = parse_data(file_name);
    if (chessmen == NULL) {
        printf("no figures\n");
        return -1;
    }
    set_chessmen(&board, chessmen);
    print_board(&board);
    for (size_t cur = slist_first(chessmen); cur != slist_stop(chessmen); cur = slist_next(chessmen, cur)) {
        check_attack(*(void**)slist_current(chessmen, cur), &board);
    }

    delete_data(chessmen);
    return 0;
}