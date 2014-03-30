
typedef struct {

	char *filename;
	int is_directory;

	void *thumb_cache;
	int is_cached;

} filenav_file_t;

#define FILENAV_MIN_ENTRIES 15

typedef struct {
	filenav_file_t *head;
	size_t reserved_entries;
	size_t entry_count;

	size_t screen_ofs;
	size_t screen_size;
	size_t cursor;
} filenav_list_t;

extern filenav_list_t* filenav_readdir(const char *dir, int hidden_files, size_t screen_size);
extern void filenav_free(filenav_list_t *fl);
extern const filenav_file_t * filenav_get(filenav_list_t *fl, size_t nr);
extern int filenav_setthumb(filenav_list_t *fl, size_t nr, void *data, size_t size);
extern void filenav_next(filenav_list_t *fl);
extern void filenav_prev(filenav_list_t *fl);
extern void filenav_nextpage(filenav_list_t *fl);
extern void filenav_prevpage(filenav_list_t *fl);
extern size_t filenav_getcursor(filenav_list_t *fl);
extern size_t filenav_getscreenofs(filenav_list_t *fl);
