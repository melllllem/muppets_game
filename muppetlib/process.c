#include "process.h"

void idleProc(World *world, ActiveStateMachine *activeTile) {
	if (activeTile->type == STATE_MACHINE_MUPPET) {
		if (world->frameOfset % 10 == 0) {
			activeTile->data.muppet.food--;
		}

		if (activeTile->data.muppet.food <= 0) activeTile->dead = 1;
		else activeTile->dead = 0;
	}
}

void process(World *world) {
	world->frameOfset++;

	for (uint16_t i=0; i<world->activeTileCount; i++) {
		ActiveStateMachine *activeTile = &world->activeTiles[i];

		handleanim(activeTile);
		handleGravity(world, activeTile);
		idleProc(world, activeTile);

		if (activeTile->dead) continue;
		handleGoal(world, activeTile);
		handleActiveMovement(world, activeTile);
	}
}
