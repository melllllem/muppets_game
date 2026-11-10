#include "mossplant.h"

#include "../muppetmath.h"

uint16_t newMossPlant(World *world, Coord coord) {
	if (addActiveTile(world, coord)) return 1;

	ActiveStateMachine *activeTile = getActiveTile(world, coord);
	if (!activeTile) {
		printf("newMossPlant: cant find activeTile\n");
		return 1;
	}

	uint16_t maxGrowth = getRandi(MOSS_PLANT_PEAK_GROWTH_MIN, MOSS_PLANT_PEAK_GROWTH_MAX);
	activeTile->data.mossplant.maxGrowthStage = maxGrowth;

	setTile(&world->map[coord.x][coord.y], MOSSPLANT, TXT_MOSSPLANT);
	return 0;
}

void idleProcMossPlant(World *world, ActiveStateMachine *activeTile) {
	if (activeTile->type != STATE_MACHINE_MOSSPLANT) return;

	if (activeTile->data.mossplant.growhtStage < activeTile->data.mossplant.maxGrowthStage)
		activeTile->data.mossplant.growhtStage++;
}
