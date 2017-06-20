#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

/*
 * 
 */

// Структура хранящая список содержимого каталога в виде
// массива строк (аля argv). Память для записей выделяется
// из кучи.

typedef struct {
    unsigned int count;
    char **list;
} my_dirslist;

/// Очищает динамическую память принятой структуры
/// и возвращает и возвращает такуюже структуру заполненную новыми данными. 
/// \param dl
/// \param dst_name
/// \return 

int dirs_list(my_dirslist *dl, char *dst_name) {
    // Очищает кучу по адресам из принятой структуры.
    while (dl->count) {
        free(*(dl->list + dl->count));
        dl->count--;
        if (!dl->count)
            free(dl->list);
    }


    dl->list = (char**) malloc(sizeof (char*));
    DIR *DIRp;
    struct dirent *current_dir;
    // Открываем каталог.
    DIRp = opendir(dst_name);
    // Если вернулся не NULL начинаем обходить записи данного каталога.
    if (DIRp) {
        // Повторяем пока не NULL т.е. пока не закончились записи.
        while ((current_dir = readdir(DIRp)) != NULL) {
            // Выделяем место под название каталога.
            *(dl->list + dl->count) = malloc(strlen(current_dir->d_name) + 1);
            // Копируем имя в список.
            strcpy(*(dl->list + dl->count), current_dir->d_name);
            //*((*(dl->list + dl->count)) + strlen(current_dir->d_name) + 1) = '\0';
            dl->count++;
            dl->list = realloc(dl->list, sizeof (void*) * (dl->count + 1));
        }
        return 0;
    } else
        return -1;

}

/*
 *
 */


