#include <ncurses.h>
#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "dirfncs.h"

#define BOTTOM_BORDER 5

int main(int argc, char **argv) {

    // Содержит код нажатой клавиши.
    unsigned int pressed_key = 0;
    // Текущая позиция "курсора" в списке.
    unsigned int position = 0;

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
    mdirs = dirs_list(".");

    while (true) {

        if (pressed_key == KEY_UP && position > 0)
            position--;
        if (pressed_key == KEY_DOWN && position < mdirs->count - 1)
            position++;

        // Если нажат ENTER
        if (pressed_key == '\n') {
            // Переходим в каталог на котором нажали ENTER
            chdir(*(mdirs->list + position));
            // Освобождаем память занятую предыдущим списком.
            dirs_list_free(mdirs);
            // Освобождаем память переменной.
            free(mdirs);
            // Загружаем список файлов нового каталога. 
            mdirs = dirs_list(".");
            // Обнуляем позицию.
            position = 0;
            // Обнуляем чтобы не зациклилось.
            pressed_key = ' ';
            continue;
        }

        // Выход по нажатию клавиши 'q'
        if (pressed_key == 'q')
            break;
        
        // Отображает текущий каталог в заголовке.
        // Valgrind говорит что в этой функции иногда происходят ошибки.
        printw("\n > %s\n", get_current_dir_name());

        // Переменная хранящая позицию с которой 
        // начинать выводить список файлов.
        int tmp_pos = 0;
        // Вычисляем номер элемента с которого выводить список если
        // курсор ушел за нижний край.
        if (position + BOTTOM_BORDER > getmaxy(mwin)) {
            tmp_pos = position - getmaxy(mwin);
            tmp_pos += 4;
        }

        // Вывод списка.
        for (; tmp_pos < mdirs->count; tmp_pos++) {
            if (tmp_pos == position) {
                attron(COLOR_PAIR(1));
                printw("    %s\n", *(mdirs->list + tmp_pos));
                attroff(COLOR_PAIR(1));
            } else
                printw("    %s\n", *(mdirs->list + tmp_pos));
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

    // Тут можно не очищать, но так из Valgrind исчезат лишняя инфа.
    dirs_list_free(mdirs);
    free(mdirs);

    // Чтобы после выхода терминал не чудил.
    refresh();
    endwin();

}
