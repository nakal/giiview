
#ifndef IIVIEW_MODULES_INCLUDED
#define IIVIEW_MODULES_INCLUDED

/*

   modules.h


Infos: see modules.c
*/

/*
   Small explanation of the module structure:

   extension_count	- number of file extensions which will be used
			   to identify an image to be in this module
   extension		- pointer to a list with extensions which will be used
			   to identify an image to be in this module (please
			   don't use same extensions for different modules!)
   open			- opens the image file and reads in all data, so
			   the methods getpixel, getwidth and getheight will
			   become accessible
   close		- closes the image file and frees all space used by
			   the module
   getpixel		- returns the RGB pixel value at specified position
			   in the image parameters are x,y and a boolean value
			   which requests a color-mode (1=color 2=b&w)
   getwidth		- width of the image
   getheight		- height of the image
   */

typedef struct {
	const char	**extension;
	int		(*open)(const char *, size_t, size_t);
	void		(*close)(void);
	unsigned int	(*getpixel)(size_t, size_t);
	size_t		(*getwidth)(void);
	size_t		(*getheight)(void);
} module_t;

extern const module_t * modules_module_for_filename(const char *filename);

#endif
