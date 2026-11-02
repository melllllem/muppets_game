#include "process.h"

void process(World *world) {
	world->frameOfset++;

	for (uint16_t i=0; i<world->activeTileCount; i++) {
		ActiveStateMachine *activeTile = &world->activeTiles[i];

		handleanim(activeTile);

		if (activeTile->dead) continue;
		handleGoal(world, activeTile);
		handleActiveMovement(world, activeTile);
	}
}
