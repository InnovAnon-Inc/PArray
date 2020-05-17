# Install the pkg-config file.
pkgconfigdir = $(libdir)/pkgconfig
#pkgconfig_DATA = src/libparray.pc src/parray-test.pc
pkgconfig_DATA = src/libparray.pc

DISTCLEANFILES = $(pkgconfig_DATA)
#EXTRA_DIST = src/libparray.pc.in src/parray-test.pc.in
EXTRA_DIST = src/libparray.pc.in

SUBDIRS = src
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -I m4

