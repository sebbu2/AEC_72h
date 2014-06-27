DEBUG=-O0 -g -D_DEBUG
#DEBUG+=-fno-lto
CPPFLAGS=$(DEBUG) -D__USE_MINGW_ANSI_STDIO=1 -W -Wall -Wextra -Werror -ansi -pedantic -pedantic-errors -Wshadow -Wconversion
CC=gcc
CFLAGS=-std=c99 -Wc++-compat
CXX=g++
CXXFLAGS=-Wsign-conversion -Woverloaded-virtual -std=gnu++98 -Wno-long-long -fno-rtti -Wc++0x-compat
LD=ld
LDFLAGS=-Wl,--as-needed
#LDFLAGS+=-Wl,--reduce-memory-overheads -Wl,--no-keep-memory
LOADLIBES:=
LDLIBS=

INCLUDES=

#disable built-in implicit rules
.SUFFIXES:
#disable automatic deletion of intermediate files
.SECONDARY:
#delete output file if error occured
.DELETE_ON_ERROR:

all: envmod.exe

clean:
	@-rm *.o 2>/dev/null

distclean: clean
	@-rm *.exe 2>/dev/null

mrproper: distclean

.PHONY: all clean distclean mrproper

%.exe: %.cc.o
	$(CXX) $(DEBUG) -o $@ $(filter %.o,$^) $(LDFLAGS) $(LOADLIBES) $(LDLIBS)

%.exe: %.o
	$(CC) $(DEBUG) -o $@ $(filter %.o,$^) $(LDFLAGS) $(LOADLIBES) $(LDLIBS)

%.cc.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $@ -c $(filter %.cpp,$^)

%.cc.o: %.cxx
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $@ -c $(filter %.cxx,$^)

%.cc.o: %.cc
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $@ -c $(filter %.cc,$^)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) $(INCLUDES) -o $@ -c $(filter %.c,$^)
