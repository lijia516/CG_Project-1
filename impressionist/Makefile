#
#  Makefile for Mac platforms
#

LOCAL = /usr/local

INCLUDE = -I$(LOCAL)/include
LIBDIR =  -L$(LOCAL)/lib

LDLIBS = -L/usr/local/lib/ -framework Carbon -framework ApplicationServices -framework Cocoa
GLDLIBS = -framework AGL -framework OpenGL
LIBS  = $(LDLIBS) $(GLDLIBS) -lfltk_gl -lfltk -lfltk_images -lfltk_forms -lfltk_jpeg -lpng16 -lm

CFLAGS = -g

CC = g++

.cpp.o: 
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $*.o $<

ALL.O = bitmap.o impBrush.o \
	impressionist.o impressionistDoc.o impressionistUI.o \
	originalView.o paintView.o pointBrush.o circleBrush.o lineBrush.o \
	scatpointBrush.o scatcircleBrush.o scatlineBrush.o

impressionist: $(ALL.O)
	$(CC) $(CFLAGS) -o $@ $(ALL.O) $(INCLUDE) $(LIBDIR) $(LIBS)

clean:
	rm -f *.o impressionist

