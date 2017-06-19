//#include <ncurses.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
//#include <libio.h> // Тут define NULL
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#define MAX_ITEMS 4
#define NAME_MAX 255

// Структура хранящая список содержимого каталога в виде
// массива строк (аля argv). Память для записей выделяется
// из кучи.

typedef struct {
    unsigned int count;
    char **list;
} my_dirslist;

// Очищает динамическую память принятой структуры
// и возвращает и возвращает такуюже структуру заполненную новыми данными.

my_dirslist *dirs_list(my_dirslist *dl, char *dst_name) {
    // Очищает кучу по адресам из принятой структуры.
    while (dl->count) {
        free(*(dl->list + dl->count));
        dl->count--;
        if (!dl->count)
            free(dl->list);
    }


    dl->list = (char**) malloc(sizeof (char*));
    DIR *DIRp;
    char name[NAME_MAX];
    struct dirent *current_dir;
    // Открываем каталог.
    DIRp = opendir(dst_name);
    // Если вернулся не NULL начинаем обходить записи данного каталога.
    if (DIRp) {
        // Повторяем пока не NULL т.е. пока не закончились записи.
        while ((current_dir = readdir(DIRp)) != NULL) {
            // Выделяем место под название каталога.
            *(dl->list + dl->count) = malloc(current_dir->d_reclen + 1);
            // Копируем имя в список.
            strcpy(*(dl->list + dl->count), current_dir->d_name);
            dl->count++;
            dl->list = realloc(dl->list, dl->count + 1);
        }
        return dl;
    } else
        return NULL;

}

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
    my_dirslist *mdirs = malloc(sizeof (my_dirslist));
    memset(mdirs, 0, sizeof (my_dirslist));
    printf("%d\n", mdirs->count);
    dirs_list(mdirs, ".");


    printf("Hello!\n");
//    
//    refresh();
//    getch();
//    endwin();

}
