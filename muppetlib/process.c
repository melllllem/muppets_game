#include "process.h"

void idleProc(World *world, ActiveStateMachine *activeTile) {
	if (activeTile->type == STATE_MACHINE_MUPPET)
		idleProcMuppet(world, activeTile);
	if (activeTile->type == STATE_MACHINE_MOSSPLANT)
		idleProcMossPlant(world, activeTile);
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
