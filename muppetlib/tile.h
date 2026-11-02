#pragma once

#include "common.h"

void setTile(Tile *tile, uint8_t type, uint8_t atlas_coord);
uint8_t isTileDiggable(World *world, Coord coord);
