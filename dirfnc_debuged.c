/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dimasik
 *
 * Created on 20 июня 2017 г., 9:00
 */

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
    //char name[NAME_MAX];
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
            *((*(dl->list + dl->count)) + strlen(current_dir->d_name) + 1) = '\0';
            //printf("%s\n", *(dl->list + dl->count+1));
            //printf("%s : [%d]\n", current_dir->d_name, strlen(current_dir->d_name)); +
            dl->count++;
            dl->list = realloc(dl->list, sizeof(void*) * (dl->count + 1));
        }
        return dl;
    } else
        return NULL;

}

/*
 *
 */

int main(int argc, char** argv) {

    my_dirslist *mdir = malloc(sizeof(my_dirslist));
    memset(mdir, 0, sizeof(my_dirslist));
    dirs_list(mdir, ".");
    printf("%d\n", mdir->count);
    for (int i = mdir->count; i >= 0; i-- )
        printf("%s\n", *(mdir->list + i-1));
    return (EXIT_SUCCESS);
}

