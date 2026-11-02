#include "goal.h"

void handleGoal(World *world, ActiveStateMachine *activeTile) {
	if (activeTile->type == STATE_MACHINE_MUPPET) {
		switch (activeTile->data.muppet.goal) {
		case GOAL_DBG:
			break;

		case GOAL_NONE:
			break;

		case GOAL_FUCK:
			if (!isNextTo(world, activeTile->coord, MUPPET)) break;

			Coord spawncoord = activeTile->coord;
			Coord dstcoord = {activeTile->coord.x, activeTile->coord.y-1};

			if (!moveMuppet(world, activeTile->coord, dstcoord)) {
				//These lines need to be in this specific order for some reason
				//I do not know why
				//This is gonna come back to haunt me.
				activeTile->data.muppet.goal = GOAL_NONE;
				newMuppet(world, spawncoord);
			}
			break;
		}

		if (world->frameOfset % 10 == 0) {
			activeTile->data.muppet.food--;
			if (activeTile->data.muppet.food <= 0) activeTile->dead = 1;
		}
	}
}
