
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#include "filenav.h"

#define FILENAV_MIN_ENTRIES 15

static int filenav_readall(filenav_list_t *fl, DIR *d, int hidden_files);

filenav_list_t* filenav_readdir(const char *dir, int hidden_files, size_t screen_size) {

	DIR *d;
	filenav_list_t *fl;

	d = opendir(dir);
	if (d==NULL) return NULL;

	fl = (filenav_list_t *)malloc(sizeof(filenav_list_t));
	if (fl!=NULL) {
		fl->head = (filenav_file_t *)malloc(sizeof(filenav_file_t)*FILENAV_MIN_ENTRIES);
		if (fl->head==NULL || filenav_readall(fl, d, hidden_files)!=0) {
			free(fl);
			fl=NULL;
		}
	}

	closedir(d);

	fl->screen_ofs = 0;
	fl->cursor = 0;
	fl->screen_size = screen_size;

	return fl;
}

void filenav_free(filenav_list_t *fl) {

	size_t i=0;

	while (i<fl->reserved_entries) {
		if (i<fl->entry_count) {
			free(fl->head[i].filename);
			if (fl->head[i].is_cached) free(fl->head[i].thumb_cache);
		}
		free(fl->head);
		i++;
	}

	free(fl);
}

static int filenav_readall(filenav_list_t *fl, DIR *d, int hidden_files) {

	struct dirent *ent;

	while ((ent=readdir(d))!=NULL) {

		filenav_file_t *cur;

		if (fl->entry_count>=fl->reserved_entries) {

			size_t newcount;
			filenav_file_t *newhead;

			/* reallocate */
			newcount = fl->reserved_entries * 2;
			newhead = realloc(fl->head, newcount);
			if (newhead == NULL) {
				fprintf(stderr, "Out of memory.\n");
				break;
			}

			fl->head = newhead;
			fl->reserved_entries = newcount;
		}

		cur = fl->head+fl->entry_count;

		cur->filename = (char *)malloc(ent->d_namlen+1);
		if (cur->filename==NULL) {
			fprintf(stderr, "Out of memory.\n");
			break;
		}

		strcpy(cur->filename, ent->d_name);
		cur->is_directory = (ent->d_type & DT_DIR) != 0;
		cur->thumb_cache = NULL;
		cur->is_cached = 0;

		fl->entry_count++;
	}

	/* need sort */

	return fl->entry_count<=0;
}

const filenav_file_t * filenav_get(filenav_list_t *fl, size_t nr) {

	if (nr>=fl->entry_count) return NULL;
	else return fl->head+nr;
}

int filenav_setthumb(filenav_list_t *fl, size_t nr, void *data, size_t size) {

	if (nr>=fl->entry_count) return -1;
	if ((fl->head[nr].thumb_cache = malloc(size))==NULL) return -1;

	memcpy(fl->head[nr].thumb_cache, data, size);
	fl->head[nr].is_cached = 1;

	return 0;
}

void filenav_next(filenav_list_t *fl) {

	if (fl->cursor+1>=fl->entry_count) return;

	fl->cursor++;
	if (fl->cursor-fl->screen_ofs>=fl->screen_size) fl->screen_ofs=fl->cursor-fl->screen_size+1;
}

void filenav_prev(filenav_list_t *fl) {

	if (fl->cursor==0) return;

	fl->cursor--;
	if (fl->cursor<fl->screen_ofs) fl->screen_ofs=fl->cursor;
}

void filenav_nextpage(filenav_list_t *fl) {

	fl->cursor += fl->screen_size;
	if (fl->cursor>=fl->entry_count) fl->cursor=fl->entry_count-1;
	fl->screen_ofs += fl->screen_size;

	if (fl->screen_ofs+fl->screen_size-1>=fl->entry_count)
		fl->screen_ofs = fl->entry_count >= fl->screen_size ?
		fl->entry_count - fl->screen_size : 0;
}

void filenav_prevpage(filenav_list_t *fl) {

	if (fl->cursor<=fl->screen_size) {
		fl->cursor=0;
		fl->screen_ofs=0;
	} else {
		fl->cursor-=fl->screen_size;

		if (fl->screen_ofs<=fl->screen_size) {
			fl->screen_ofs=0;
		} else {
			fl->screen_ofs-=fl->screen_size;
		}
	}
}

size_t filenav_getcursor(filenav_list_t *fl) {
	return fl->cursor;
}

size_t filenav_getscreenofs(filenav_list_t *fl) {
	return fl->screen_ofs;
}

