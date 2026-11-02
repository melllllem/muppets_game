#pragma once

#include "common.h"
#include "activestatemachine.h"
#include "anim.h"
#include "entities/muppet.h"
#include "goal.h"
#include "movement.h"

void idleProc(World *world, ActiveStateMachine *activeTile);
void process(World *world);
