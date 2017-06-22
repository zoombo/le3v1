#include <ncurses.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "dirfncs.h"

#define NAME_MAX 255

int main(int argc, char **argv) {

    //const char *marr[MAX_ITEMS] = {"Item1", "Item2", "Item3", "Item4"};

    unsigned int pressed_key = 0;
    unsigned int position = 0;

    dirslist_t mdirs;
    memset(&mdirs, 0, sizeof (dirslist_t));

    initscr();
    keypad(stdscr, true);

    dirs_list(&mdirs, ".");

    while (true) {

        if (pressed_key == KEY_UP && position > 0) {
            position--;
            //printw("UP\n");
        }
        if (pressed_key == KEY_DOWN && position < mdirs.count - 1) {
            position++;
            //printw("DOWN\n");
        }
        if (pressed_key == 'e') {
            printw("\n\n  ENTER pressed\n");
            chdir(*(mdirs.list + position));
            printw("\n\n  Entered: %s\n", *(mdirs.list + position));
            dirs_list_free(&mdirs);
            dirs_list(&mdirs, ".");
            position = 0;
            pressed_key = ' ';
            continue;
        }

        if (pressed_key == 'q')
            break;

        printw("\n");
        for (int i = 0; i < mdirs.count-i; i++) {
            if (i == position)
                printw("  > %s\n", *(mdirs.list + i));
            else
                printw("    %s\n", *(mdirs.list + i));
        }

        wborder(stdscr, '*', '*', '*', '*', '+', '+', '+', '+');
        pressed_key = getch();
        clear();
        refresh();


    }



    /*
        my_dirslist mdirs;
        memset(&mdirs, 0, sizeof (my_dirslist));
     */

    ////+//// dirs_list(&mdirs, ".");
    //printf("%d\n", mdirs.count);
    ////+////for (int i = mdirs.count - 1; i >= 0; i--)
    ////+////printf("%s\n", *(mdirs.list + i));
    /*
        // DEBUG. 
        chdir("..");
        printf("--------------\n");
        dirs_list(&mdirs, ".");
        //printf("%d\n", mdirs.count);
        for (int i = mdirs.count - 1; i >= 0; i--)
            printf("%s\n", *(mdirs.list + i));
        // END_DEBUG.     
     */
    ////+////    dirs_list_free(&mdirs);
    //printf("Hello!\n");

    //  
    refresh();
    getch();
    endwin();


}
