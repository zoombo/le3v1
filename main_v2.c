#include <stdbool.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

/*
*
*/

// Структура хранящая список содержимого каталога в виде
// массива строк (аля argv). Память для записей выделяется
// из кучи.

typedef struct {
	unsigned int count;
	char **list;
} dirslist_t;


/// Очищает кучу по адресам из принятой структуры.
/// \param dl

void dirs_list_free(dirslist_t *dl) {

	dl->count--;
	 
	while (dl->count) {
		free(*(dl->list + dl->count));
		dl->count--;

		if (!dl->count) {
			free(*(dl->list));
			free(dl->list);
		}

	}
}


/// Возвращает указатель на структуру dirslist_t заполненную новыми данными. 
/// \param dl
/// \param dst_name
/// \return 

dirslist_t *dirs_list(char *dst_name) {

	dirslist_t *dl = malloc(sizeof(dirslist_t));

	// Создаем новые записи. Сразу закинем в начало списка
	// обозначения дочернего и родительского каталогов.
	dl->list = (char**)malloc(sizeof(char*) * 3);

	*(dl->list) = malloc(sizeof(char) * sizeof("."));
	strcpy(*(dl->list), ".");

	*(dl->list + 1) = malloc(sizeof(char) * sizeof(".."));
	strcpy(*(dl->list + 1), "..");
	// Указваем что в списке уже есть два элемента.
	dl->count = 2;


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
			*(dl->list + dl->count) = malloc(strlen(current_dir->d_name) + 1);
			// Копируем имя в список.
			strcpy(*(dl->list + dl->count), current_dir->d_name);

			// Увеличиваем список.
			dl->count++;
			dl->list = realloc(dl->list, sizeof(char*) * (dl->count + 1));

		}
		//!!!_Если раскомментировать этот printf то упадет раньше_!!!
		//printf("%d\n", (int) dl->count);
		closedir(DIRp);
		return dl;
	}
	else {
		printf("Return: NULL!\n");
		return NULL;
	}

}
////////////////////////////////////////////////////////////////////////////////

int main(int argc, char **argv) {


	dirslist_t *mdirs;

	for (int k = 0; k < 10; k++) {
		mdirs = dirs_list(".");
		for (int i = 0; i < mdirs->count; i++) {
			printf("%s\n", *(mdirs->list + i));
		}
		dirs_list_free(mdirs);
		free(mdirs);

		chdir("..");
	}

}
