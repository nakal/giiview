
/* Abstraction layer for handling different image formats. */

#include <string.h>
#include <ctype.h>

#include "modules.h"

#include "jpeg.h"
#include "gif.h"
#include "bmp.h"
#include "tiff.h"
#include "png.h"

static const char *jpeg_extensions[] = { "jpg", "jpeg", NULL };
static const char *gif_extensions[]={ ".gif" , NULL };
static const char *bmp_extensions[]={ ".bmp", NULL };
static const char *tiff_extensions[]={ ".tif", ".tiff", ".nef", NULL };
static const char *png_extensions[]={ ".png", NULL };

static const module_t module[] = {
	{ jpeg_extensions, open_jpeg, close_jpeg, getpixel_jpeg, getwidth_jpeg, getheight_jpeg } ,
	{ gif_extensions, GIF_OpenFile, GIF_CloseFile, GIF_GetPixel, GIF_GetWidth, GIF_GetHeight },
	{ bmp_extensions, BMP_OpenFile, BMP_CloseFile, BMP_GetPixel, BMP_GetWidth, BMP_GetHeight },
	{ tiff_extensions, TIF_OpenFile, TIF_CloseFile, TIF_GetPixel, TIF_GetWidth, TIF_GetHeight },
	{ png_extensions, PNG_OpenFile, PNG_CloseFile, PNG_GetPixel, PNG_GetWidth, PNG_GetHeight },
	{ NULL, NULL, NULL, NULL, NULL, NULL }
};

static const module_t * modules_module_for_extension(const char *extension);

const module_t * modules_module_for_filename(const char *filename)
{
	const char *ext;
	char extension[32];
	char *p;

	ext = strrchr(filename, '.');
	if (ext == NULL) return NULL;

	strlcpy(extension, ext+1, sizeof(extension));
	if (extension[0]==0) return NULL;

	for (p=extension; *p != '\0'; p++) *p = tolower(*p);

	return modules_module_for_extension(extension);
}

static const module_t * modules_module_for_extension(const char *extension)
{
	size_t m, i;

	for (m=0; module[m].extension != NULL; m++) {
		for (i=0; module[i].extension != NULL; i++) {
			if (strcmp(extension, module[m].extension[i]))
				return &module[m];
		}
	}

	return NULL;
}
