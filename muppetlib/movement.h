#pragma once

#include "activestatemachine.h"
#include "world.h"
#include "entities/muppet.h"

void handleGravity(World *world, ActiveStateMachine *activeTile);
void handleActiveMovement(World *world, ActiveStateMachine *activeTile);
