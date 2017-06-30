#pragma once

// Структура описывающая окно-панель со списком файлов.

struct pane {
    // Указатель на хендл окна.
    WINDOW *pane_window;
    dirlist_t *dirlist;
    // Позиция списка в окне.
    unsigned int position;
    // Позиция выделения окне.
    unsigned int real_position;
    
    // Полный путь до текущего каталога.
    char *current_directory;
    // Указывает на то что окно активно в данный момент.
    _Bool is_active;
    
    // Позиция окна по X.
    unsigned int x_position;
    // Позиция окна по Y.
    unsigned int y_position;
    // Размер окна по X.
    unsigned int x_len;
    // Размер окна по Y.
    unsigned int y_len;
    // Что еще?..
};
