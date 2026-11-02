#include "muppetlib/window.h"
#include "muppetlib/world.h"
#include "muppetlib/res.h"
#include "muppetlib/process.h"
#include "muppetlib/render.h"
#include "muppetlib/input.h"

int main() {
	init();

	World *world = newWorld();
	if (!world) return 1;

	worldInit(world);
	if (loadres(world)) return 1;

	while (!shouldQuit()) {
		handleInput(world);
		process(world);
		render(world);
	}

	endWorld(&world);
	quit();
	return 0;
}
