#include "activestatemachine.h"

uint16_t addActiveTile(World *world, Coord coord) {
	ActiveStateMachine *tmp = realloc(world->activeTiles, (world->activeTileCount + 1) * sizeof(ActiveStateMachine));
	if (!tmp) {
		printf("addActiveTile: unable to add active tile\n");
		return 1;
	}
	world->activeTiles = tmp;

	world->activeTiles[world->activeTileCount] = (ActiveStateMachine){0};
	world->activeTiles[world->activeTileCount].coord = coord;
	world->activeTileCount++;

	return 0;
}

void moveActiveTile(World *world, Coord tile, Coord dst) {
	//check if tile is indeed an activetile
	for (uint16_t i=0; i<world->activeTileCount; i++) {
		if (coordCmp(world->activeTiles[i].coord, tile)) {

			//change the coordinates
			world->activeTiles[i].coord.x = dst.x;
			world->activeTiles[i].coord.y = dst.y;
		}
	}
}

ActiveStateMachine *getActiveTile(World *world, Coord coord) {
	for (uint16_t i=0; i<world->activeTileCount; i++) {
		if (coordCmp(world->activeTiles[i].coord, coord)) {
			return &world->activeTiles[i];
		}
	}
	return NULL;
}
