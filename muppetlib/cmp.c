#include "cmp.h"

uint16_t coordCmp(Coord a, Coord b) {
	return (a.x == b.x && a.y == b.y);
}

uint8_t matchTile(World *world, Coord coord, uint8_t type) {
	if (world->map[coord.x][coord.y].type == type) return 1;
	return 0;
}

uint8_t isNextTo(World *world, Coord coord, uint8_t type) {
	uint8_t left   = world->map[coord.x-1][coord.y].type;
	uint8_t right  = world->map[coord.x+1][coord.y].type;

	return (
		left == type ||
		right == type
	);
}

uint8_t isSurroundedBy(World *world, Coord coord, uint8_t type) {
	uint8_t top    = world->map[coord.x][coord.y-1].type;
	uint8_t bottom = world->map[coord.x][coord.y+1].type;
	uint8_t left   = world->map[coord.x-1][coord.y].type;
	uint8_t right  = world->map[coord.x+1][coord.y].type;

	uint8_t topleft     = world->map[coord.x-1][coord.y-1].type;
	uint8_t bottomleft  = world->map[coord.x-1][coord.y+1].type;
	uint8_t topright    = world->map[coord.x+1][coord.y-1].type;
	uint8_t bottomright = world->map[coord.x+1][coord.y+1].type;

	return (
		top == type &&
		bottom == type &&
		left == type &&
		right == type &&

		topleft == type &&
		bottomleft == type &&
		topright == type &&
		bottomright == type
	);
}
