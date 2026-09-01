# Minimal, self-contained build of faToTwoBit / twoBitToFa / twoBitInfo
# for offline HPC (no root, no dev packages, old gcc).
#
# This directory carries the exact kent-src subset needed (src/), so it can
# be cloned anywhere and built with nothing but gcc + make:
#
#   make           # builds faToTwoBit twoBitToFa twoBitInfo
#   make clean     # removes binaries and all intermediate files (obj/)
#   make CC=icc    # use a different compiler if needed
#
# It replaces the normal kent build (userApp.mk -> jkweb.a), which drags in
# MySQL, OpenSSL, libpng, freetype, htslib, libcurl and zlib.  These three
# programs need NONE of them - the result links against libc/libm only
# (verified with ldd):
#
#   ldd faToTwoBit  ->  libc.so.6
#
# How the heavy dependencies are avoided:
#   * lib/udc.c lib/net.c lib/https.c  -> replaced by udcLocal.c
#     (local-file-only UDC; remote URLs abort with a clear message)
#   * htslib (tabix support of linefile.c)  -> replaced by htsStub.c
#     (lineFileTabixMayOpen just returns NULL / warns); only the htslib
#     headers under src/htslib are used, no htslib code is compiled
#   * freetype  -> freeType.c is compiled WITHOUT -DUSE_FREETYPE, so it
#     provides its own errAbort stubs; bitmap fonts are built-in source
#
# src/ is a minimal snapshot of kent-src determined from linker map files;
# it is not modified in any way.  Licensing: see LICENSE (MIT, UC Regents)
# and src/htslib/LICENSE (MIT/Expat, Genome Research Ltd).

kentSrc = src

CC ?= gcc
CFLAGS += -O2 -std=c99 -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_GNU_SOURCE
INCLUDES = -I$(kentSrc)/inc -I$(kentSrc)/htslib

PROGRAMS = faToTwoBit twoBitToFa twoBitInfo

# The exact set of kent src/lib objects referenced (directly or transitively)
# by the three programs, determined from linker map files.
LIB = \
    aliType asParse base64 basicBed binRange bits bPlusTree cheapcgi colHash \
    common dlist dnaseq dnautil dystring errAbort fa ffAli filePath freeType \
    gemfont hash htmlColor htmshell intExp kxTok linefile localmem memalloc \
    memgfx mgCircle mgPolygon mime obscure options osunix pipeline portimpl psl \
    rangeTree rbTree servBrcMcw servcis servcl servCrunx servmsII servpws \
    sqlList sqlNum tokenizer twoBit verbose wildcmp

# bitmap fonts pulled in by memgfx (via basicBed in twoBitToFa)
FONTS = $(basename $(notdir $(wildcard $(kentSrc)/lib/font/*.c)))

# local replacements for udc/net/https and htslib
STUBS = udcLocal htsStub

LIBOBJS = $(LIB:%=obj/%.o) $(FONTS:%=obj/%.o) $(STUBS:%=obj/%.o)

# where to find the sources
vpath %.c \
    $(kentSrc)/lib \
    $(kentSrc)/lib/font \
    $(kentSrc)/utils \
    .

all: $(PROGRAMS)

lib2bit.a: $(LIBOBJS)
	ar rcs $@ $^

faToTwoBit: obj/faToTwoBit.o lib2bit.a
	$(CC) $(CFLAGS) -o $@ obj/faToTwoBit.o lib2bit.a -lm

twoBitToFa: obj/twoBitToFa.o lib2bit.a
	$(CC) $(CFLAGS) -o $@ obj/twoBitToFa.o lib2bit.a -lm

twoBitInfo: obj/twoBitInfo.o lib2bit.a
	$(CC) $(CFLAGS) -o $@ obj/twoBitInfo.o lib2bit.a -lm

obj/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# obj/ holds the .o intermediate files; they are 100% regenerable, so
# clean removes them together with the binaries and the archive.
clean:
	rm -rf obj lib2bit.a $(PROGRAMS)

.PHONY: all clean
