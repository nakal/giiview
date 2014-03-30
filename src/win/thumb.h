
#ifndef THUMB_H_INCLUDED
#define THUMB_H_INCLUDED

#include <gtk/gtk.h>

typedef struct {
	size_t width;
	size_t height;
	size_t grid_index;
} thumb_configuration_t;

extern GtkWidget *thumb_get_empty(const thumb_configuration_t *config);
extern GtkWidget *thumb_from_image(const thumb_configuration_t *config,
	const char *path);

#endif
