struct pane {
	WINDOW *pane_window;
	
	dirlist_t *dirlist;
	unsigned int position;
	unsigned int real_position;
	
	char *current_directory;
	
	_Bool is_active;
	
}