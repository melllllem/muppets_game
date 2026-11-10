#include "muppet.h"

void revive(ActiveStateMachine *activeTile) {
	activeTile->dead = 0;
	activeTile->type = STATE_MACHINE_MUPPET;
	activeTile->movementDelay = MUPPET_DEFAULT_MOVEMENT_DELAY;
	activeTile->data.muppet.animSet.whichanim = ANIM_IDLE;
	activeTile->data.muppet.goal = GOAL_NONE;
	activeTile->data.muppet.food = MUPPET_FOOD_INITIAL;
	activeTile->data.muppet.target = activeTile->coord;
}

uint16_t moveMuppet(World *world, Coord muppet, Coord dst) {
	//bounds checking
	if (dst.x >= WORLD_SIZE_X || dst.y >= WORLD_SIZE_Y) return 1;
	if (muppet.x >= WORLD_SIZE_X || muppet.y >= WORLD_SIZE_Y) return 1;

	Tile *muppetTile = &world->map[muppet.x][muppet.y];
	Tile *dstTile = &world->map[dst.x][dst.y];
	
	//tiletype validation
	if (!isTileDiggable(world, (Coord){dst.x, dst.y})) return 1;

	//'delete' the old tile
	setTile(muppetTile, AIR, TXT_AIR);

	//modify the new tile
	setTile(dstTile, MUPPET, TXT_MUPPET);

	//move the coordinates of the active tile tracking this muppet
	moveActiveTile(world, muppet, dst);

	return 0;
}

uint16_t newMuppet(World *world, Coord coord) {
	if (world->map[coord.x][coord.y].type == MUPPET) return 1;

	if(addActiveTile(world, coord)) return 1;

	ActiveStateMachine *activeTile = getActiveTile(world, coord);
	if (!activeTile) {
		printf("newMuppet: did not find active tile\n");
		return 1;
	}

	revive(activeTile);
	setAnimData(&activeTile->data.muppet.animSet.walkAnim, 0, 2, 10);
	setAnimData(&activeTile->data.muppet.animSet.idleAnim, 2, 2, 10);
	setAnimData(&activeTile->data.muppet.animSet.deadAnim, 4, 1, 10);
	setAnimData(&activeTile->data.muppet.animSet.attackAnim, 6, 1, 10);

	setTile(&world->map[coord.x][coord.y], MUPPET, TXT_MUPPET);

	return 0;
}

void setMuppetTarget(World *world, Coord muppet, Coord target) {
	ActiveStateMachine *activeTile = getActiveTile(world, muppet);
	if (!activeTile) {
		printf("setMuppetTarget: coordinate does not point to an active tile\n");
		return;
	}

	activeTile->data.muppet.target = target;
}


void idleProcMuppet(World *world, ActiveStateMachine *activeTile) {
	if (world->frameOfset % 10 == 0) {
		activeTile->data.muppet.food--;
	}

	if (activeTile->data.muppet.food <= 0) activeTile->dead = 1;
	else activeTile->dead = 0;
}
