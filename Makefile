#
# Basic Makefile
#

CC=g++
LD=$(CC)
CPPFLAGS=-g -Wall
LDFLAGS=-L/usr/local/lib -lSDL2 -lSDL2_image
INCLUDES=-I./src -I./include -I/usr/local/include/SDL2

INSTALL=/usr/bin/install -c

.cpp.o: %.cpp
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $@ -c $<

cabrio: src/main.o src/Config.o src/Game.o src/GameList.o src/Image.o src/Logger.o src/Platform.o \
	src/Quad.o src/Renderer.o src/RendererOpenGL.o
	$(LD) -o $@ $^ $(LDFLAGS)

clean:
	rm -f cabrio src/*.o core core.*
