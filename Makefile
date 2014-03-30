
CFLAGS+=-Wall -Wstrict-prototypes -Wmissing-prototypes -pedantic

OBJS=\
	src/main/main.o \
	src/win/mainwin.o \
	src/win/thumb.o \
	src/data/filenav.o \
	src/formats/modules.o \
	src/formats/bmp.o \
	src/formats/gif.o \
	src/formats/jpeg.o \
	src/formats/png.o \
	src/formats/tiff.o

CFLAGS+=`pkg-config --cflags gtk+-3.0`
LDFLAGS+=-ljpeg -ltiff -lpng -lz

LIBS=`pkg-config --libs gtk+-3.0`

all: $(OBJS)
	$(CC) $(LDFLAGS) -o giiview $(OBJS) $(LIBS)

src/main/main.o: src/main/main.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/win/mainwin.o: src/win/mainwin.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/win/thumb.o: src/win/thumb.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/data/filenav.o: src/data/filenav.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/formats/modules.o: src/formats/modules.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/formats/bmp.o: src/formats/bmp.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/formats/gif.o: src/formats/gif.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/formats/jpeg.o: src/formats/jpeg.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/formats/png.o: src/formats/png.c
	$(CC) $(CFLAGS) -c -o $@ $<

src/formats/tiff.o: src/formats/tiff.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)
