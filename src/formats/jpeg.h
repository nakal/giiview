
#ifndef IIVIEW_NJPEG_INCLUDED
#define IIVIEW_NJPEG_INCLUDED

/*

   njpeg.h
   -------


*/

extern int  open_jpeg(const char *filename, size_t request_width, size_t request_height);
extern void close_jpeg(void);
extern unsigned int  getpixel_jpeg(size_t x, size_t y);
extern size_t getwidth_jpeg(void);
extern size_t getheight_jpeg(void);

#endif

