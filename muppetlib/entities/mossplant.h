#pragma once

#include "../common.h"
#include "../anim.h"
#include "../activestatemachine.h"
#include "../cmp.h"
#include "../tile.h"

uint16_t newMossPlant(World *world, Coord coord);
void idleProcMossPlant(World *world, ActiveStateMachine *activeTile);
