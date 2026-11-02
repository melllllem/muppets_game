#remember to specify your C compiler
BUILDFLAGS = -lraylib
CFLAGS = -O0

ifneq ($(DEBUG), true)
	CFLAGS = -O3
endif

ifeq ($(OS), Windows_NT)
	BUILDFLAGS += -static -lopengl32 -lgdi32 -lwinmm -luser32 -lshell32
	ifneq ($(DEBUG), true)
		BUILDFLAGS += -mwindows
	endif
endif

build: build/muppets.exe

run: build/muppets.exe
	cd build && ./muppets.exe

clean:
	rm tmp/main.o
	rm tmp/activestatemachine.o
	rm tmp/anim.o
	rm tmp/cmp.o
	rm tmp/goal.o
	rm tmp/input.o
	rm tmp/muppet.o
	rm tmp/process.o
	rm tmp/render.o
	rm tmp/res.o
	rm tmp/tile.o
	rm tmp/window.o
	rm tmp/world.o
	rm build/muppets.exe
	rm tmp/movement.o

build/muppets.exe: tmp/main.o tmp/activestatemachine.o tmp/anim.o tmp/cmp.o tmp/goal.o tmp/input.o tmp/muppet.o tmp/process.o tmp/render.o tmp/res.o tmp/tile.o tmp/window.o tmp/world.o tmp/movement.o
	$(CC) $(CFLAGS) tmp/main.o tmp/movement.o tmp/activestatemachine.o tmp/anim.o tmp/cmp.o tmp/goal.o tmp/input.o tmp/muppet.o tmp/process.o tmp/render.o tmp/res.o tmp/tile.o tmp/window.o tmp/world.o -o build/muppets.exe $(BUILDFLAGS)

tmp/main.o: main.c common.h
	$(CC) $(CFLAGS) -c main.c -o tmp/main.o

tmp/activestatemachine.o: muppetlib/activestatemachine.c muppetlib/activestatemachine.h common.h
	$(CC) $(CFLAGS) -c muppetlib/activestatemachine.c -o tmp/activestatemachine.o

tmp/anim.o: muppetlib/anim.c muppetlib/anim.h common.h
	$(CC) $(CFLAGS) -c muppetlib/anim.c -o tmp/anim.o

tmp/cmp.o: muppetlib/cmp.c muppetlib/cmp.h common.h
	$(CC) $(CFLAGS) -c muppetlib/cmp.c -o tmp/cmp.o

tmp/goal.o: muppetlib/goal.c muppetlib/goal.h common.h
	$(CC) $(CFLAGS) -c muppetlib/goal.c -o tmp/goal.o

tmp/input.o: muppetlib/input.c muppetlib/input.h common.h
	$(CC) $(CFLAGS) -c muppetlib/input.c -o tmp/input.o

tmp/muppet.o: muppetlib/entities/muppet.c muppetlib/entities/muppet.h common.h
	$(CC) $(CFLAGS) -c muppetlib/entities/muppet.c -o tmp/muppet.o

tmp/process.o: muppetlib/process.c muppetlib/process.h common.h
	$(CC) $(CFLAGS) -c muppetlib/process.c -o tmp/process.o

tmp/render.o: muppetlib/render.c muppetlib/render.h common.h
	$(CC) $(CFLAGS) -c muppetlib/render.c -o tmp/render.o

tmp/res.o: muppetlib/res.c muppetlib/res.h common.h
	$(CC) $(CFLAGS) -c muppetlib/res.c -o tmp/res.o

tmp/tile.o: muppetlib/tile.c muppetlib/tile.h common.h
	$(CC) $(CFLAGS) -c muppetlib/tile.c -o tmp/tile.o

tmp/window.o: muppetlib/window.c muppetlib/window.h common.h
	$(CC) $(CFLAGS) -c muppetlib/window.c -o tmp/window.o

tmp/world.o: muppetlib/world.c muppetlib/world.h common.h
	$(CC) $(CFLAGS) -c muppetlib/world.c -o tmp/world.o

tmp/movement.o: muppetlib/movement.c muppetlib/movement.h common.h
	$(CC) $(CFLAGS) -c muppetlib/movement.c -o tmp/movement.o
