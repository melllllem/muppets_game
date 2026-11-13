#pragma once

#include "common.h"
#include "tile.h"
#include "muppetmath.h"
#include "cmp.h"
#include "entities/mossplant.h"
#include "entities/muppet.h"

World *newWorld();
void endWorld(World **world);
void worldInit(World *world);
