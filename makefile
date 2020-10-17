WINBUILD = x86_64-w64-mingw32-g++-win32
c= g++
WINLIBS = -lSDL2
LIBS = -lSDL2
PATHS = -I/usr/include/SDL2

interpreter: chip8.o run.o opcodes.o
	$(c) chip8.o run.o opcodes.o -o chip8 $(LIBS) -ggdb

chip8.o: chip8.cpp
	$(c) -c chip8.cpp -Wall -ggdb

run.o: run.cpp
	$(c) -c run.cpp $(PATHS) -ggdb

opcodes.o: opcodes.cpp
	$(c) -c opcodes.cpp -Wall


win: chip8w.o runw.o
	$(WINBUILD) chip8w.o runw.o -o chip8win $(WINLIBS)

chip8w.o: chip8.cpp
	$(WINBUILD) -c chip8.cpp -Wall -o chip8w.o

runw.o: run.cpp
	$(WINBUILD) -c run.cpp $(PATHS) -o runw.o

clean:
	-rm *.o chip8 chip8win