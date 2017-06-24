#pragma once

typedef struct {
    unsigned int count;
    char **list;
} dirslist_t;

void dirs_list_free(dirslist_t *dl);
dirslist_t *dirs_list(char *dst_name);

enum item_type {
    ISDIR = 10,
    ISFILE
};

struct item {
    char *name;
    enum item_type itype;
};


