#include "world.h"

World *newWorld() {
	World *world = calloc(1, sizeof(World));
	if (!world) {
		printf("newWorld: unable to allocate world\n");
	}

	return world;
}

void carve_cave(World *world, Coord coord, uint16_t itter) {
	for (uint16_t i=0; i<itter; i++) {
		setTile(&world->map[coord.x][coord.y], AIR, TXT_AIR);
		
		uint64_t vecx = getRandi(0, 2);
		if (vecx == 0) {
			coord.x++;
		} else if (vecx == 1) {
			coord.x--;
		}
			
		uint64_t vecy = getRandi(0, 2);
		if (vecy == 0) {
			coord.y++;
		} else if (vecy == 1) {
			coord.y--;
		}
	}
}

void remove_floating_blocks(World *world) {
	for (uint16_t x=1; x<WORLD_SIZE_X-1; x++) {
		for (uint16_t y=1; y<WORLD_SIZE_Y-1; y++) {
			if (
				world->map[x][y].type != AIR &&
				world->map[x+1][y].type == AIR &&
				world->map[x-1][y].type == AIR &&
				world->map[x][y+1].type == AIR &&
				world->map[x][y-1].type == AIR
			) setTile(&world->map[x][y], AIR, TXT_AIR);
		}
	}
}

void worldInit(World *world) {
	world->activeTileCount = 0;
	world->activeTiles = NULL;

	world->camera = (Camera2D){0};
	world->camera.zoom = 2.0f;
	world->camera.target.y = (GROUND_LAYER - 10) * TILE_RES;
	world->camera.target.x = WORLD_SIZE_X/2 * TILE_RES;
	
	printf("Gen: filling world\n");
	for (uint16_t x=0; x<WORLD_SIZE_X; x++) {
		for (uint16_t y=0; y<GROUND_LAYER; y++) {
			setTile(&world->map[x][y], AIR, TXT_AIR);
		}

		for (uint16_t y=GROUND_LAYER; y<WORLD_SIZE_Y; y++) {
			setTile(&world->map[x][y], DIRT, TXT_DIRT);
		}
	}

	printf("Gen: generating caves\n");
	//TODO: make a function that generates more
	carve_cave(world, (Coord){WORLD_SIZE_X/2, GROUND_LAYER+15}, 100);
	printf("Gen: removing floating blocks\n");
	remove_floating_blocks(world);
	printf("Gen: finished\n");
}

void endWorld(World **world) {
	for (uint16_t i=0; i<TEXTURE_ATLAS_SIZE; i++) {
		UnloadTexture((*world)->res.textureAtlas[i]);
	}

	free((*world)->activeTiles);
	free(*world);
	
	*world = NULL;
}
