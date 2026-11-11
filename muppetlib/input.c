#include "input.h"

void handleInput(World *world) {

	world->camera.zoom += GetMouseWheelMove() * CAMERA_ZOOM_SPEED;
	if (world->camera.zoom > ZOOM_MAX) world->camera.zoom = ZOOM_MAX;
	if (world->camera.zoom < ZOOM_MIN) world->camera.zoom = ZOOM_MIN;

	float zoomLevel = world->camera.zoom;

	if (IsKeyPressed(KEY_F11)) toggleFullScreen();

	if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP))	world->camera.target.y -= CAMERA_SPEED / zoomLevel;
	if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) world->camera.target.y += CAMERA_SPEED / zoomLevel;
	if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))	world->camera.target.x -= CAMERA_SPEED / zoomLevel;
	if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) world->camera.target.x += CAMERA_SPEED / zoomLevel;

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		uint16_t x = (GetMouseX() / zoomLevel + world->camera.target.x) / TILE_RES;
		uint16_t y = (GetMouseY() / zoomLevel + world->camera.target.y) / TILE_RES;

		if (IsKeyDown(KEY_U)) {
			newMuppet(world, (Coord){x, y});
			return;
		}

		if (IsKeyDown(KEY_I)) {
			setTile(&world->map[x][y], DBG, TXT_DBG);
			return;
		}

		if (IsKeyDown(KEY_O)) {
			ActiveStateMachine *activeTile = getActiveTile(world, (Coord){x, y});
			if (!activeTile) return;

			activeTile->data.muppet.goal = GOAL_FUCK;
			return;
		}

		if (IsKeyDown(KEY_H)) {
			ActiveStateMachine *activeTile = getActiveTile(world, (Coord){x, y});
			if (!activeTile) return;

			activeTile->data.muppet.goal = GOAL_NONE;
			return;
		}
		
		if (IsKeyDown(KEY_J)) {
			ActiveStateMachine *activeTile = getActiveTile(world, (Coord){x, y});
			if (!activeTile) return;

			activeTile->data.muppet.goal = GOAL_DBG;
			return;
		}

		if (IsKeyDown(KEY_K)) {
			ActiveStateMachine *activeTile = getActiveTile(world, (Coord){x, y});
			if (!activeTile) return;

			activeTile->data.muppet.food = 0;
			return;
		}

		if (IsKeyDown(KEY_L)) {
			ActiveStateMachine *activeTile = getActiveTile(world, (Coord){x, y});
			if (!activeTile) return;

			revive(activeTile);
			return;
		}

		if (IsKeyDown(KEY_SEMICOLON)) {
			newMossPlant(world, (Coord){x, y});
			return;
		}

		uint16_t sx = world->currentSelected.x;
		uint16_t sy = world->currentSelected.y;

		Tile *selected = &world->map[sx][sy];
		
		if (selected->type == MUPPET) {
			setMuppetTarget(world, (Coord){sx, sy}, (Coord){x, y});
			world->currentSelected = (Coord){0};
			
		} else {
			world->currentSelected.x = x;
			world->currentSelected.y = y;
		}
	}
}
