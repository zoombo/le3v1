//#include <ncurses.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
//#include <libio.h> // Тут define NULL
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "dirfncs.h"

#define MAX_ITEMS 4
#define NAME_MAX 255


int main(int argc, char **argv) {
    /*
            const char *marr[MAX_ITEMS] = {"Item1", "Item2", "Item3", "Item4"};
            unsigned int updwn = 0;
            unsigned int position = 0;

            initscr();
            keypad(stdscr, true);

            while (true)
            {
                    if (updwn == KEY_UP && position > 0)
                    {
                            position--;
                            //printw("UP\n");
                    }
                    if (updwn == KEY_DOWN && position < MAX_ITEMS - 1)
                    {
                            position++;
                            //printw("DOWN\n");
                    }
                    if (updwn == 'q')
                            break;

                    printw("\n");
                    for (int i = 0; i < MAX_ITEMS; i++)
                    {
                            if (i == position)
                                    printw("  > %s\n", marr[i]);
                            else
                                    printw("    %s\n", marr[i]);
                    }

                    wborder(stdscr, '*', '*', '*', '*', '+', '+', '+', '+');
                    updwn = getch();
                    clear();



            }
     */
    //my_dirslist *mdirs = malloc(sizeof (my_dirslist));
    
    my_dirslist mdirs;
    memset(&mdirs, 0, sizeof (my_dirslist));
    
    dirs_list(&mdirs, ".");
    //printf("%d\n", mdirs.count);
    for (int i = mdirs.count - 1; i >= 0; i--)
        printf("%s\n", *(mdirs.list + i));
        
    printf("Hello!\n");
    
//    
//    refresh();
//    getch();
//    endwin();

}
