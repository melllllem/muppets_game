#pragma once

#include "../common.h"
#include "../anim.h"
#include "../activestatemachine.h"
#include "../cmp.h"
#include "../tile.h"

uint16_t newMuppet(World *world, Coord coord);
uint16_t moveMuppet(World *world, Coord muppet, Coord dst);
void revive(ActiveStateMachine *activeTile);
void setMuppetTarget(World *world, Coord muppet, Coord target);
void handleActiveMovement(World *world, ActiveStateMachine *activeTile);
