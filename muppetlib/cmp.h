#pragma once

#include "common.h"

uint8_t isNextTo(World *world, Coord coord, uint8_t type);
uint8_t matchTile(World *world, Coord coord, uint8_t type);
uint8_t isSurroundedBy(World *world, Coord coord, uint8_t type);
uint16_t coordCmp(Coord a, Coord b);
