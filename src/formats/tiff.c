
/* Decodes tiff images. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tiffio.h>

//#include "filelist.h"
#include "tiff.h"

static TIFF* tif_file;
static uint32* tif_raster=NULL;
static size_t tif_width=0;
static size_t tif_height=0;

int TIF_OpenFile(const char *filename,
    size_t width, size_t height) {

	size_t npixels;

	(void)width;
	(void)height;

	tif_raster=NULL;
	tif_file=TIFFOpen(filename,"r");

	if (tif_file) {

		TIFFGetField(tif_file, TIFFTAG_IMAGEWIDTH, &tif_width);
		TIFFGetField(tif_file, TIFFTAG_IMAGELENGTH, &tif_height);
		npixels = tif_width * tif_height;
		tif_raster = (uint32*) _TIFFmalloc((int)(npixels * sizeof (uint32)));
		if (tif_raster != NULL) {
			if (!TIFFReadRGBAImage(tif_file,tif_width,tif_height,tif_raster, 0)) {
#ifdef VERBOSE
				printf("Couldn't read raster-data.\n");
#endif
				return 0;
			}
		} else {
#ifdef VERBOSE
			printf("Couldn't get raster-data.\n");
#endif
			return 0;
		}
	} else {
#ifdef VERBOSE
		printf("Couldn't open.\n");
#endif
		return 0;
	}
	return 1;
}

void TIF_CloseFile(void) {
	if (tif_raster) _TIFFfree(tif_raster);
	if (tif_file) TIFFClose(tif_file);
	tif_file=NULL;
}

unsigned int TIF_GetPixel(size_t x, size_t y) {

	unsigned int color;

	if ((unsigned int)x>=tif_width || (unsigned int)y>=tif_height)
		return 0x000000;

	color=tif_raster[(tif_height-y-1)*tif_width+x];

	return (color&0xFF00)|((color>>16)&0xFF)|((color&0xFF)<<16);
}

size_t TIF_GetWidth(void) {
	return tif_width;
}

size_t TIF_GetHeight(void) {
	return tif_height;
}
