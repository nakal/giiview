
#ifndef IIVIEW_GIF_INCLUDED
#define IIVIEW_GIF_INCLUDED

/*

   gif.h

   These are some prototypes for gif.c.


   Update history, see in gif.c

*/

extern int GIF_OpenFile(const char *filename, size_t request_width, size_t request_height);
extern void GIF_CloseFile(void);
extern unsigned int GIF_GetPixel(size_t x, size_t y);
extern size_t GIF_GetWidth(void);
extern size_t GIF_GetHeight(void);

#endif

