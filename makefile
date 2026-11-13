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
	rm -r tmp/*
	rm build/muppets.exe

test:
	make clean
	make run

build/muppets.exe: tmp/mossplant.o tmp/main.o tmp/activestatemachine.o tmp/anim.o tmp/cmp.o tmp/goal.o tmp/input.o tmp/muppet.o tmp/process.o tmp/render.o tmp/res.o tmp/tile.o tmp/window.o tmp/world.o tmp/movement.o tmp/muppetmath.o
	$(CC) $(CFLAGS) tmp/main.o tmp/mossplant.o tmp/movement.o tmp/activestatemachine.o tmp/anim.o tmp/cmp.o tmp/goal.o tmp/input.o tmp/muppet.o tmp/process.o tmp/render.o tmp/res.o tmp/tile.o tmp/muppetmath.o tmp/window.o tmp/world.o -o build/muppets.exe $(BUILDFLAGS)

tmp/main.o: main.c muppetlib/common.h
	$(CC) $(CFLAGS) -c main.c -o tmp/main.o

tmp/activestatemachine.o: muppetlib/activestatemachine.c muppetlib/activestatemachine.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/activestatemachine.c -o tmp/activestatemachine.o

tmp/anim.o: muppetlib/anim.c muppetlib/anim.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/anim.c -o tmp/anim.o

tmp/cmp.o: muppetlib/cmp.c muppetlib/cmp.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/cmp.c -o tmp/cmp.o

tmp/goal.o: muppetlib/goal.c muppetlib/goal.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/goal.c -o tmp/goal.o

tmp/input.o: muppetlib/input.c muppetlib/input.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/input.c -o tmp/input.o

tmp/muppet.o: muppetlib/entities/muppet.c muppetlib/entities/muppet.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/entities/muppet.c -o tmp/muppet.o

tmp/process.o: muppetlib/process.c muppetlib/process.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/process.c -o tmp/process.o

tmp/render.o: muppetlib/render.c muppetlib/render.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/render.c -o tmp/render.o

tmp/res.o: muppetlib/res.c muppetlib/res.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/res.c -o tmp/res.o

tmp/tile.o: muppetlib/tile.c muppetlib/tile.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/tile.c -o tmp/tile.o

tmp/window.o: muppetlib/window.c muppetlib/window.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/window.c -o tmp/window.o

tmp/world.o: muppetlib/world.c muppetlib/world.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/world.c -o tmp/world.o

tmp/movement.o: muppetlib/movement.c muppetlib/movement.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/movement.c -o tmp/movement.o

tmp/muppetmath.o: muppetlib/muppetmath.c muppetlib/muppetmath.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/muppetmath.c -o tmp/muppetmath.o

tmp/mossplant.o: muppetlib/entities/mossplant.c muppetlib/entities/mossplant.h muppetlib/common.h
	$(CC) $(CFLAGS) -c muppetlib/entities/mossplant.c -o tmp/mossplant.o
