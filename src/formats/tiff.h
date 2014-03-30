
#ifndef IIVIEW_TIF_INCLUDED
#define IIVIEW_TIF_INCLUDED

extern int TIF_OpenFile(const char *filename, size_t request_width, size_t request_height);
extern void TIF_CloseFile(void);
extern unsigned int TIF_GetPixel(size_t x, size_t y);
extern size_t TIF_GetWidth(void);
extern size_t TIF_GetHeight(void);

#endif

