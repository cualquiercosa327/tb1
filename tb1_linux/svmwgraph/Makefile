include ../Makefile.inc

INCLUDE= $(INCLUDE_GLOBAL)
LIBS= $(LIBS_GLOBAL)

all:	libsvmwgraph.a

libsvmwgraph.a:	vmw_core.o vmw_dialogs.o vmw_flip.o vmw_font.o vmw_paintpro.o vmw_palette.o vmw_pcx.o vmw_setup.o vmw_sprite.o $(CURSES_TARGET) null_svmwgraph.o $(OPENGL_TARGET) $(SDL_TARGET)
	ar cru libsvmwgraph.a vmw_core.o vmw_dialogs.o vmw_flip.o vmw_font.o vmw_paintpro.o vmw_palette.o vmw_pcx.o vmw_setup.o vmw_sprite.o $(CURSES_TARGET) null_svmwgraph.o $(OPENGL_TARGET) $(SDL_TARGET)
	ranlib libsvmwgraph.a

vmw_core.o:	vmw_core.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_core.c

vmw_dialogs.o:	vmw_dialogs.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_dialogs.c

vmw_flip.o:	vmw_flip.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_flip.c

vmw_font.o:	vmw_font.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_font.c

vmw_paintpro.o:	vmw_paintpro.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_paintpro.c

vmw_palette.o:	vmw_palette.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_palette.c

vmw_pcx.o:	vmw_pcx.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_pcx.c

vmw_setup.o:	vmw_setup.c
	$(CC) $(CFLAGS) $(INCLUDE) $(SDL_FLAGS) $(CURSES_FLAGS) $(OPENGL_FLAGS) -c vmw_setup.c

vmw_sprite.o:	vmw_sprite.c
	$(CC) $(CFLAGS) $(INCLUDE) -c vmw_sprite.c

curses_svmwgraph.o:	curses_svmwgraph.c
	$(CC) $(CFLAGS) $(INCLUDE) -c curses_svmwgraph.c $(CURSES_FLAGS)

null_svmwgraph.o:	null_svmwgraph.c
	$(CC) $(CFLAGS) $(INCLUDE) -c null_svmwgraph.c

opengl_svmwgraph.o:	opengl_svmwgraph.c
	$(CC) $(CFLAGS) $(INCLUDE) -c opengl_svmwgraph.c

sdl_svmwgraph.o:	sdl_svmwgraph.c
	$(CC) $(CFLAGS) $(INCLUDE) -c sdl_svmwgraph.c

clean:
	rm -f libsvmwgraph.a *.o *~
