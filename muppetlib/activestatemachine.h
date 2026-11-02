#pragma once

#include "common.h"
#include "cmp.h"

uint16_t addActiveTile(World *world, Coord coord);
void moveActiveTile(World *world, Coord tile, Coord dst);
ActiveStateMachine *getActiveTile(World *world, Coord coord);
