#include "render.h"

void render(World *world) {
	if (!world) {
		BeginDrawing();
		EndDrawing();
		return;
	}

	BeginDrawing();
	BeginMode2D(world->camera);

	ClearBackground(BLACK);

	float zoomLevel = world->camera.zoom;

	uint16_t screenwidth = GetScreenWidth();
	uint16_t screenheight = GetScreenHeight();

	uint16_t originx = (uint16_t)((world->camera.target.x) / TILE_RES);
	uint16_t originy = (uint16_t)((world->camera.target.y) / TILE_RES);

	uint16_t targetx = (uint16_t)((world->camera.target.x + screenwidth / zoomLevel) / TILE_RES + 1);
	uint16_t targety = (uint16_t)((world->camera.target.y + screenheight / zoomLevel) / TILE_RES + 1);

	if (originx > WORLD_SIZE_X) originx = 0;
	if (targetx > WORLD_SIZE_X) targetx = 0;
	if (originy > WORLD_SIZE_X) originy = 0;
	if (originx > WORLD_SIZE_X) originx = 0;

	//draw map
	for (uint16_t x=originx; x<targetx; x++) {
		for (uint16_t y=originy; y<targety; y++) {
			DrawTexture(
				world->res.textureAtlas[world->map[x][y].atlascoord],
				x*TILE_RES,
				y*TILE_RES,
				WHITE
			);
		}
	}

	for (uint16_t i=0; i<world->activeTileCount; i++) {
		ActiveStateMachine *activetile = &world->activeTiles[i];
		if (activetile->coord.x < originx || activetile->coord.x > targetx) break;
		if (activetile->coord.y < originy || activetile->coord.y > targety) break;

		AnimData *animdata = getAnimData(activetile);
		AnimSet *animset = &activetile->data.muppet.animSet;

		if (!animdata) {
			printf("render: active tile does not have any valid animation running.");
			break;
		}

		DrawTexture(
			world->res.animatlas[animdata->animOfset + animset->animProgress],
			world->activeTiles[i].coord.x * TILE_RES,
			world->activeTiles[i].coord.y * TILE_RES,
			WHITE
		);

		if (world->frameOfset % animdata->frameLen == 0) animset->animProgress++;
		if (animset->animProgress >= animdata->animLen) animset->animProgress = 0;
	}

	//draw selected tile boundary
	DrawTexture(
		world->res.textureSelect,
		world->currentSelected.x*TILE_RES,
		world->currentSelected.y*TILE_RES,
		WHITE
	);

	EndMode2D();
	EndDrawing();
}
