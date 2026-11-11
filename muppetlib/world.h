#pragma once

#include "common.h"
#include "tile.h"
#include "muppetmath.h"
#include "cmp.h"

World *newWorld();
void endWorld(World **world);
void worldInit(World *world);
