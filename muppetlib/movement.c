#include "movement.h"

void handleGravity(World *world, ActiveStateMachine *activeTile) {
	if (activeTile->type == STATE_MACHINE_MUPPET) {

		if (isSurroundedBy(world, activeTile->coord, AIR))
			moveMuppet(world, activeTile->coord, (Coord){activeTile->coord.x, activeTile->coord.y+1});
	}
}

void handleActiveMovement(World *world, ActiveStateMachine *activeTile) {
	if (activeTile->type == STATE_MACHINE_MUPPET) {
		if (world->frameOfset % activeTile->movementDelay != 0) return;

		if (activeTile->coord.x == activeTile->data.muppet.target.x) {
			if (activeTile->coord.y > activeTile->data.muppet.target.y) {
				Coord dst = {activeTile->coord.x, activeTile->coord.y-1};

				Coord left = {activeTile->coord.x-1, activeTile->coord.y};
				Coord right = {activeTile->coord.x+1, activeTile->coord.y};
				Coord top = {activeTile->coord.x, activeTile->coord.y-1};
				Coord topleft = {activeTile->coord.x-1, activeTile->coord.y-1};
				Coord topright = {activeTile->coord.x+1, activeTile->coord.y-1};

				if (
					!matchTile(world, left, AIR) ||
					!matchTile(world, right, AIR) ||
					!matchTile(world, top, AIR) ||
					!matchTile(world, topleft, AIR) ||
					!matchTile(world, topright, AIR)
				) {
					moveMuppet(world, activeTile->coord, dst);
				}
			
			} else if (activeTile->coord.y < activeTile->data.muppet.target.y) {
				Coord dst = {activeTile->coord.x, activeTile->coord.y+1};

				moveMuppet(world, activeTile->coord, dst);
			}

		} else {
			if (activeTile->coord.x > activeTile->data.muppet.target.x) {
				Coord dst = {activeTile->coord.x-1, activeTile->coord.y};
				
				moveMuppet(world, activeTile->coord, dst);
			
			} else if (activeTile->coord.x < activeTile->data.muppet.target.x) {
				Coord dst = {activeTile->coord.x+1, activeTile->coord.y};

				moveMuppet(world, activeTile->coord, dst);
			}
		}
	}
}
