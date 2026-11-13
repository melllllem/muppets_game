#include "world.h"

World *newWorld() {
	World *world = calloc(1, sizeof(World));
	if (!world) {
		printf("newWorld: unable to allocate world\n");
	}

	return world;
}

void carve_simple_cave(World *world, Coord coord, uint32_t itter) {
	for (uint32_t i=0; i<itter; i++) {
		if (coord.x < WORLD_SIZE_X && coord.y < WORLD_SIZE_Y)
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

void remove_empty_pockets(World *world) {
	for (uint16_t x=1; x<WORLD_SIZE_X-1; x++) {
		for (uint16_t y=1; y<WORLD_SIZE_Y-1; y++) {
			if (
				world->map[x][y].type == AIR &&
				world->map[x+1][y].type == DIRT &&
				world->map[x-1][y].type == DIRT &&
				world->map[x][y+1].type == DIRT &&
				world->map[x][y-1].type == DIRT
			) setTile(&world->map[x][y], DIRT, TXT_DIRT);
		}
	}
}

Coord dropdown(World *world, Coord coord, uint8_t on, uint8_t top, uint16_t max) {
	while (world->map[coord.x][coord.y].type != top || world->map[coord.x][coord.y+1].type != on) {
		if (coord.y >= max) return coord;
		coord.y++;
	}
	
	return coord;
}

void generate_moss_cave(World *world, Coord coord) {
	uint32_t size = getRandi(20, 150);
	carve_simple_cave(world, (Coord){coord.x, coord.y}, size);

	uint16_t xmin = coord.x - size/10;
	uint16_t xmax = coord.x + size/10;
	uint16_t ymin = coord.y - size/50;
	uint16_t ymax = coord.y + size/10;
	if (xmin < 0) xmin = 0;
	if (xmax > WORLD_SIZE_X) xmax = WORLD_SIZE_X;
	if (ymin < GROUND_LAYER) ymin = GROUND_LAYER;
	if (ymax > WORLD_SIZE_Y) ymax = WORLD_SIZE_Y;

	for (uint8_t i=0; i<MOSS_CAVE_DENSITY; i++)
	for (uint16_t x = xmin; x<xmax; x++) {
		Coord res = dropdown(world, (Coord){x, ymin}, DIRT, AIR, ymax);
		if (res.y == ymax) continue;
		newMossPlant(world, res);
	}
}

void generate_moss_caves(World *world) {
	for (uint32_t x=0; x<WORLD_SIZE_X; x++) {
		for (uint32_t y=GROUND_LAYER+15; y<WORLD_SIZE_Y; y++) {
			if (getRandi(0, MOSS_CAVE_DISTRIBUTION) != 0) continue;

			generate_moss_cave(world, (Coord){x, y});
		}
		printf("%u/%u\n", x, WORLD_SIZE_X);
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

	printf("Gen: generating starter cave\n");
	generate_moss_cave(world, (Coord){WORLD_SIZE_X/2+10, GROUND_LAYER+10});
	printf("Gen: generating moss caves\n");
	//generate_moss_caves(world);
	printf("Gen: removing floating blocks\n");
	remove_floating_blocks(world);
	printf("Gen: removing air pockets\n");
	remove_empty_pockets(world);
	printf("Gen: spawning muppets\n");
	newMuppet(world, (Coord){WORLD_SIZE_X/2+5, GROUND_LAYER-1});
	newMuppet(world, (Coord){WORLD_SIZE_X/2+10, GROUND_LAYER-1});
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
