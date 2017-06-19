#include <ncurses.h>
#include <stdbool.h>

#define MAX_ITEMS 4

int main(int argc, char **argv)
{

	const char *marr[MAX_ITEMS] = {"Item1", "Item2", "Item3", "Item4"};
	unsigned int updwn = 0;
	unsigned int position = 0;

	initscr();
	keypad(stdscr, true);

	while (true) {
		if (updwn == KEY_UP && position > 0) {
			position--;
			//printw("UP\n");
		}
		if (updwn == KEY_DOWN && position < MAX_ITEMS - 1) {
			position++;
			//printw("DOWN\n");
		}
		if (updwn == 'q')
			break;

		printw("\n");
		for (int i = 0; i < MAX_ITEMS; i++) {
			if (i == position)
				printw("  > %s\n", marr[i]);
			else
				printw("    %s\n", marr[i]);
		}
		
		wborder(stdscr, '.', '.', '.', '.', '.', '.', '.', '.');
		updwn = getch();
		clear();
		//refresh();


	}


	printw("Hello!\n");
	refresh();
	getch();
	endwin();

}
