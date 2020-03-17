CC      = g++
CFLAGS  = -O2 -Wall
LDLIBS  = -lX11 -lXpm -lXext
LDFLAGS =       # different includes for different OS's
BINDIR  = /usr/X11R6/bin
TARGET  = bbbutton
SRC = bbbutton.cc bbbrc.cc main.cc
OBJ = bbbutton.o bbbrc.o main.o

ALL = bbbutton

bogus:
	@echo "Usage: make <systype>"


bbbutton:	$(OBJ)
	$(CC) $(CFLAGS) -o bbbutton $(OBJ) $(LDLIBS) -L/usr/X11R6/lib -L/usr/include/lib

linux:
	make -e $(ALL) LDFLAGS='-L/usr/X11R6/lib -L/usr/include/lib'

freebsd:
	make -e $(ALL) CFLAGS='-I/usr/X11R6/include -L/usr/X11R6/lib \
	-L/usr/include/lib -L/usr/X11R6/include/X11'

clean::
	rm -f *.o ${TARGET} core

install:
	install -c -s -o root -g root -m 555 ${TARGET} ${BINDIR}
	if [ ! -f ${HOME}/.bbbuttonrc ] ; then cp .bbbuttonrc ${HOME} ; fi

uninstall:
	cd ${BINDIR} && rm ${TARGET}
