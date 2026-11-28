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

		float zoomLevel = world->camera.zoom;

		uint16_t screenwidth = GetScreenWidth();
		uint16_t screenheight = GetScreenHeight();

		uint16_t originx = (uint16_t)((world->camera.target.x) / TILE_RES);
		uint16_t originy = (uint16_t)((world->camera.target.y) / TILE_RES);

		uint16_t targetx = (uint16_t)((world->camera.target.x + screenwidth / zoomLevel) / TILE_RES + 1);
		uint16_t targety = (uint16_t)((world->camera.target.y + screenheight / zoomLevel) / TILE_RES + 1);

		if (originx > WORLD_SIZE_X) originx = 0;
		if (targetx > WORLD_SIZE_X) targetx = 0;
		if (originy > WORLD_SIZE_X) originy = 0;
		if (originx > WORLD_SIZE_X) originx = 0;

		if (!activeTile->offscreenproc && (
			activeTile->coord.x < originx ||
			activeTile->coord.x > targetx ||
			activeTile->coord.y < originy ||
			activeTile->coord.y > targety
		)) continue;

		handleanim(activeTile);
		handleGravity(world, activeTile);
		idleProc(world, activeTile);

		if (activeTile->dead) continue;
		handleGoal(world, activeTile);
		handleActiveMovement(world, activeTile);
	}
}
