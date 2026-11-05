#include "mossplant.h"


uint16_t newMossPlant(World *world, Coord coord) {
	if (addActiveTile(world, coord)) return 1;
}

void idleProcMossPlant(World *world, ActiveStateMachine *activeTile) {

}
