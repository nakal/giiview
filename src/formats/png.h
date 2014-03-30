
#ifndef IIVIEW_PNG_INCLUDED
#define IIVIEW_PNG_INCLUDED

extern int PNG_OpenFile(const char *filename, size_t request_width, size_t request_height);
extern void PNG_CloseFile(void);
extern unsigned int PNG_GetPixel(size_t x, size_t y);
extern size_t PNG_GetWidth(void);
extern size_t PNG_GetHeight(void);

#endif

