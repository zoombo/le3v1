typedef struct {
    unsigned int count;
    char **list;
} my_dirslist;

int dirs_list(my_dirslist *dl, char *dst_name);