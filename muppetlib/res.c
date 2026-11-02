#include "res.h"

uint16_t loadres(World *world) {
	
	Image atlas = LoadImage(TEXTURE_ATLAS_PATH);
	if (!IsImageValid(atlas)) {
		printf("loadres: cannot find: %s\n", TEXTURE_ATLAS_PATH);
		return 1;
	}

	for (uint16_t i=0; i<TEXTURE_ATLAS_SIZE; i++) {
		Image tile = ImageCopy(atlas);
		ImageCrop(&tile, (Rectangle){0, i*TILE_RES, TILE_RES, TILE_RES});
		world->res.textureAtlas[i] = LoadTextureFromImage(tile);

		UnloadImage(tile);
	}

	UnloadImage(atlas);

	Image select_texture = LoadImage(TEXTURE_SELECT_PATH);
	if (!IsImageValid(select_texture)) {
		printf("loadres: cannot find: %s\n", TEXTURE_SELECT_PATH);
		return 1;
	}

	world->res.textureSelect = LoadTextureFromImage(select_texture);

	UnloadImage(select_texture);

	Image animAtlas = LoadImage(ANIM_ATLAS_PATH);
	if (!IsImageValid(animAtlas)) {
		printf("loadres: cannot find %s\n", ANIM_ATLAS_PATH);
		return 1;
	}

	for (uint16_t i=0; i<ANIM_ATLAS_SIZE; i++) {
		Image tile = ImageCopy(animAtlas);
		ImageCrop(&tile, (Rectangle){0, i*TILE_RES, TILE_RES, TILE_RES});
		world->res.animatlas[i] = LoadTextureFromImage(tile);

		UnloadImage(tile);
	}

	UnloadImage(animAtlas);
	return 0;
}
