#include "tile.h"

void setTile(Tile *tile, uint8_t type, uint8_t atlas_coord) {
	*tile = (Tile){
		.type = type,
		.atlascoord = atlas_coord
	};
}

uint8_t isTileDiggable(World *world, Coord coord) {
	uint8_t type = world->map[coord.x][coord.y].type;
	uint8_t undigableTiles[] = UNDIGABLE_TILES;
	
	for (uint16_t i=0; i<countof(undigableTiles); i++) {
		if (type == undigableTiles[i]) return 0;
	}

	return 1;
}
