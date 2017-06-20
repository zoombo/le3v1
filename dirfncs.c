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


/// Очищает кучу по адресам из принятой структуры.
/// \param dl

void dirs_list_free(my_dirslist *dl) {

    while (dl->count) {
        free(*(dl->list + dl->count));
        dl->count--;

        if (!dl->count) {
            free(*(dl->list)); // Valgrind - Must have!
            free(dl->list);
        }

    }
}


/// Очищает динамическую память принятой структуры
/// и возвращает и возвращает такуюже структуру заполненную новыми данными. 
/// \param dl
/// \param dst_name
/// \return 

int dirs_list(my_dirslist *dl, char *dst_name) {

    // Очищаем старые данные.
    dirs_list_free(dl);

    // Создаем новые записи. Сразу закинем в начало списка
    // обозначения дочернего и родительского каталогов.
    dl->list = (char**) malloc(sizeof (char*) * 3);

    *(dl->list) = malloc(sizeof (char) * sizeof ("."));
    strcpy(*(dl->list), ".");

    *(dl->list + 1) = malloc(sizeof (char) * sizeof (".."));
    strcpy(*(dl->list + 1), "..");
    // Указваем что в списке уже есть два элемента.
    dl->count = 2;


    // dl->list = (char**)malloc(sizeof(char*) * 3);

    // Структура описатель "потока" каталога.
    DIR *DIRp;
    // Структура описатель текущего каталога.
    struct dirent *current_dir;
    // Открываем каталог.
    DIRp = opendir(dst_name);
    // Если вернулся не NULL начинаем обходить записи данного каталога.
    if (DIRp) {
        // Повторяем пока не NULL т.е. пока не закончились записи.
        while ((current_dir = readdir(DIRp)) != NULL) {

            if (!strcmp(current_dir->d_name, "."))
                continue;
            if (!strcmp(current_dir->d_name, ".."))
                continue;

            // Выделяем место под название каталога.
            *(dl->list + dl->count) = malloc(strlen(current_dir->d_name));
            // Копируем имя в список.
            strcpy(*(dl->list + dl->count), current_dir->d_name);
            //*((*(dl->list + dl->count)) + strlen(current_dir->d_name) + 1) = '\0';

            // Увеличиваем список.
            dl->count++;
            dl->list = realloc(dl->list, sizeof (char*) * (dl->count + 1));

        }
        closedir(DIRp);
        return 0;
    } else
        return -1;

}

