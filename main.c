#include <ncurses.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "dirfncs.h"

#define BOTTOM_BORDER 5

int main(int argc, char **argv) {

    // Содержит код нажатой клавиши.
    unsigned int pressed_key = 0;
    // Текущая позиция "курсора" в списке.
    unsigned int position = 0;
    unsigned int real_position = 0;

    dirslist_t *mdirs;

    // Инициализация окна ncurses
    WINDOW *mwin = initscr();

    // Не выводить нажатые клавиши
    noecho();
    // Цветные рамка и выделение.
    start_color();

    // Цвет курсора.
    init_pair(1, COLOR_BLACK, COLOR_BLUE);
    // Цвет рамки.
    init_pair(2, COLOR_BLACK, COLOR_CYAN);

    // Управление клавиатурой.
    keypad(stdscr, true);

    // Получаем список файлов каталога в котором запущена программа.
    mdirs = items_list(".");

    while (true) {
        /*
         * Тут странная логика которая сделана для правильного 
         * перемещения курсора по списку внутри окна.
         * real_position - позиция указывающая на элемент списка.
         * position - позиция списка выводимого в окно.
         * BOTTOM_BORDER - ширина рамки.
         * Положение position зависит от real_position так:
         *   если real_position становится больше position, значит курсор
         *   уходит за нижний край, значит увеличиваем position;
         *   
         *   если real_position становится меньше position, значит курсор
         *   уходит за верхний край, значит уменьшаем position.
         */
        if (pressed_key == KEY_UP) {
            if (real_position > 0)
                real_position--;
            if (real_position < (position + BOTTOM_BORDER) - getmaxy(mwin))
                if (position > 0)
                    position--;
        }
        if (pressed_key == KEY_DOWN) {
            if (position < mdirs->count - 1) {
                real_position++;
                if (real_position > position)
                    position++;
            }
        }

        // Если нажат ENTER
        if (pressed_key == '\n') {

            // Тут запуск файла.
            if ((*(mdirs->ilist + real_position))->itype == ISFILE) {
                char work[255];
                // Тут строим полный путь к запускаемому файлу.
                strcpy(work, getcwd(NULL, 255));
                strcat(work, "/");
                strcat(work, (*(mdirs->ilist + real_position))->name);

                //printw("\n\n %s\n", work);
                // Временно закрываем окно 
                clear();
                refresh();
                endwin();
                printf("\n%s\n", work);
                pid_t ipid;
                ipid = fork();
                if (ipid == 0) {
                    execl(work, work, NULL);
                    //execl("/usr/bin/ls", "/usr/bin/ls", "-al", NULL);
                    exit(0);
                }
                // Что-то типа лога.
                // FILE *file_ptr = fopen("le3_log.log", "w");
                // fprintf(file_ptr, "\n %s - %s \n", work, "was executed.\n");
                // fclose(file_ptr);
                                
                int statuss;
                wait(&statuss);
                getch();
                pressed_key = ' ';
                // Снова открываем окно.
                mwin = initscr();
                continue;
            }


            // Переходим в каталог на котором нажали ENTER
            chdir((*(mdirs->ilist + real_position))->name);
            // Освобождаем память занятую предыдущим списком.
            items_list_free(mdirs);
            // Освобождаем память переменной.
            free(mdirs);
            // Загружаем список файлов нового каталога. 
            mdirs = items_list(".");
            // Обнуляем позицию.
            position = 0;
            real_position = 0;
            // Обнуляем чтобы не зациклилось.
            pressed_key = ' ';
            continue;
        }

        // Выход по нажатию клавиши 'q'
        if (pressed_key == 'q')
            break;

        // Отображает текущий каталог в заголовке.
        // Valgrind говорит что в этой функции иногда происходят ошибки.
        printw("\n > %s\n", getcwd(NULL, 255));

        // Переменная хранящая позицию с которой 
        // начинать выводить список файлов.
        int tmp_pos = 0;
        //if (real_position)
        // Вычисляем номер элемента с которого выводить список если
        // курсор ушел за нижний край.
        if (position + BOTTOM_BORDER > getmaxy(mwin)) {
            tmp_pos = position - getmaxy(mwin);
            tmp_pos += 4;
        }

        // Вывод списка.
        for (; tmp_pos < mdirs->count; tmp_pos++) {
            if (tmp_pos == real_position) {
                attron(COLOR_PAIR(1));

                if ((*(mdirs->ilist + tmp_pos))->itype == ISDIR)
                    printw("    /%s\n", (*(mdirs->ilist + tmp_pos))->name);

                if ((*(mdirs->ilist + tmp_pos))->itype == ISFILE)
                    printw("    %s\n", (*(mdirs->ilist + tmp_pos))->name);

                attroff(COLOR_PAIR(1));
            } else {
                if ((*(mdirs->ilist + tmp_pos))->itype == ISDIR)
                    printw("    /%s\n", (*(mdirs->ilist + tmp_pos))->name);

                if ((*(mdirs->ilist + tmp_pos))->itype == ISFILE)
                    printw("    %s\n", (*(mdirs->ilist + tmp_pos))->name);
            }
        }

        // Этими макросами окружаем элементы
        // которые должны быть цветными.
        attron(COLOR_PAIR(2));
        wborder(stdscr, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        attroff(COLOR_PAIR(2));

        // Ждем нового нажатия клавиши.
        pressed_key = getch();
        // Очищаем экран для следующей отрисовки.
        clear();

    }

    // Тут можно не очищать, но так из Valgrind исчезает лишняя инфа.
    items_list_free(mdirs);
    free(mdirs);

    // Чтобы после выхода терминал не чудил.
    refresh();
    endwin();

}
