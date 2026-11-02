#include "world.h"

World *newWorld() {
	World *world = calloc(1, sizeof(World));
	if (!world) {
		printf("newWorld: unable to allocate world\n");
	}

	return world;
}

void worldInit(World *world) {
	world->activeTileCount = 0;
	world->activeTiles = NULL;

	world->camera = (Camera2D){0};
	world->camera.zoom = 2.0f;
	world->camera.target.y = (GROUND_LAYER - 10) * TILE_RES;
	world->camera.target.x = WORLD_SIZE_X/2 * TILE_RES;
	
	//fill in the tiles
	for (uint16_t x=0; x<WORLD_SIZE_X; x++) {
		for (uint16_t y=0; y<GROUND_LAYER; y++) {
			setTile(&world->map[x][y], AIR, TXT_AIR);
		}

		for (uint16_t y=GROUND_LAYER; y<WORLD_SIZE_Y; y++) {
			setTile(&world->map[x][y], DIRT, TXT_DIRT);
		}
	}
}

void endWorld(World **world) {
	for (uint16_t i=0; i<TEXTURE_ATLAS_SIZE; i++) {
		UnloadTexture((*world)->res.textureAtlas[i]);
	}

	free((*world)->activeTiles);
	free(*world);
	
	*world = NULL;
}
