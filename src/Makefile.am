bin_PROGRAMS = fuseiso
fuseiso_SOURCES = fuseiso.c isofs.c

# set the include path found by configure
INCLUDES= $(all_includes)

# the library search path.
fuseiso_LDFLAGS = $(all_libraries)
noinst_HEADERS = isofs.h

AM_CFLAGS = -D_FILE_OFFSET_BITS=64 `pkg-config --cflags fuse glib-2.0` -Wall
AM_LDFLAGS = `pkg-config --libs fuse glib-2.0` -lz
