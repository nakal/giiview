
#include <string.h>

#include "thumb.h"

static GtkWidget *thumb_empty = NULL;

typedef struct {
	size_t x_count;
	size_t y_count;
} thumb_grid_t;

#define thumb_AVAILABLE_SIZES	4
static const thumb_grid_t thumb_grid[4] = {
	{ 12, 9 },
	{ 9, 6 },
	{ 6, 4 },
	{ 4, 3 },
};

static thumb_configuration_t recent_configuration = {
	0, 0, 0xffff
};

static GtkWidget *thumb_alloc(const thumb_configuration_t *config);

GtkWidget *thumb_get_empty(const thumb_configuration_t *config)
{
	gboolean allocate = FALSE;

	if (thumb_empty == NULL) allocate = TRUE;
	else {
		if (memcmp(&recent_configuration, config,
			sizeof(thumb_configuration_t))!=0) {

			g_object_unref(thumb_empty);
			allocate = TRUE;
		}
	}

	if (allocate) {
		thumb_empty = thumb_alloc(config);
		gtk_image_clear(GTK_IMAGE(thumb_empty));
	}

	return thumb_empty;
}

static GtkWidget *thumb_alloc(const thumb_configuration_t *config)
{
	GdkPixbuf *pixbuf;
	GtkWidget *image;

	pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 24,
		config->width/thumb_grid[config->grid_index].x_count,
		config->height/thumb_grid[config->grid_index].y_count);

	image = gtk_image_new_from_pixbuf(pixbuf);

	memcpy(&recent_configuration, config, sizeof(thumb_configuration_t));

	return image;
}

GtkWidget *thumb_from_image(const thumb_configuration_t *config,
	const char *path)
{
	GdkPixbuf *pixbuf;
	GError *error;

	pixbuf = gdk_pixbuf_new_from_file_at_size(path,
		config->width/thumb_grid[config->grid_index].x_count,
		config->height/thumb_grid[config->grid_index].y_count,
		&error);

	return pixbuf==NULL ? thumb_empty : gtk_image_new_from_pixbuf(pixbuf);
}
