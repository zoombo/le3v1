#pragma once

typedef struct {
    unsigned int count;
    char **list;
} my_dirslist;

void dirs_list_free(my_dirslist *dl);
int dirs_list(my_dirslist *dl, char *dst_name);




