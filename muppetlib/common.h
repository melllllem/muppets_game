#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <raylib/rlgl.h>

#define GAME_NAME "Muppets"

#define WINDOW_SIZE_X 1080
#define WINDOW_SIZE_Y 720

#define WORLD_SIZE_X 2048
#define WORLD_SIZE_Y 16384

#define GROUND_LAYER 384

#define TEXTURE_ATLAS_SIZE 256
#define ANIM_ATLAS_SIZE 2048
#define TILE_RES 16

#define TEXTURE_ATLAS_PATH "res/atlas.png"
#define TEXTURE_SELECT_PATH "res/select.png"
#define ANIM_ATLAS_PATH "res/animAtlas.png"

#define CAMERA_SPEED 10
#define CAMERA_ZOOM_SPEED 0.1

#define ZOOM_MAX 3.5f
#define ZOOM_MIN 0.5f

#define MUPPET_DEFAULT_MOVEMENT_DELAY 5
#define MUPPET_WALK_ANIM_OFSET 0
#define MUPPET_WALK_ANIM_LEN 2
#define MUPPET_FOOD_INITIAL 255
#define MUPPET_UPDATE_TIME 10

#define MOSS_PLANT_PEAK_GROWTH_MIN 180
#define MOSS_PLANT_PEAK_GROWTH_MAX 250
#define MOSS_PLANT_UPDATE_TIME 8

#define MOSS_CAVE_DISTRIBUTION 2000
#define MOSS_CAVE_DENSITY 3

typedef Texture TextureAtlas[TEXTURE_ATLAS_SIZE];
typedef Texture AnimAtlas[ANIM_ATLAS_SIZE];

typedef struct {
	TextureAtlas textureAtlas;
	Texture textureSelect;
	AnimAtlas animatlas;

} Resources;

typedef struct {
	enum : uint8_t {
		DBG,
		AIR,
		DIRT,
		MUPPET,
		MOSSPLANT,
	} type;
	
	enum : uint8_t {
		TXT_DBG,
		TXT_AIR,
		TXT_DIRT,
		TXT_MUPPET,
		TXT_MOSSPLANT,
		TXT_MOSSPLANT_EATEN,
	} atlascoord;

} Tile;

#define UNDIGABLE_TILES {DBG, MUPPET, MOSSPLANT}

typedef struct {
	uint16_t x;
	uint16_t y;

} Coord;

typedef struct {
	uint16_t animOfset;
	uint8_t animLen;
	uint8_t frameLen;

} AnimData;

typedef struct {
	enum : uint8_t {
		ANIM_IDLE,
		ANIM_WALK,
		ANIM_ATTACK,
		ANIM_DEAD,
	} whichanim;

	AnimData idleAnim;
	AnimData walkAnim;
	AnimData attackAnim;
	AnimData deadAnim;
	uint8_t animProgress;

} AnimSet;

typedef enum {
	GOAL_DBG,
	GOAL_NONE,
	GOAL_FUCK,
} Goal;

typedef enum {
	STATE_MACHINE_MUPPET,
	STATE_MACHINE_MOSSPLANT,
} ActiveStateMachineType;

typedef union {
	struct {
		Coord target;
		Goal goal;

		int16_t food;
		AnimSet animSet;
	} muppet;

	struct {
		uint8_t growhtStage;
		uint8_t maxGrowthStage;
	} mossplant;
} ActiveStateMachineData;

typedef struct {
	Coord coord;
	uint8_t movementDelay;

	ActiveStateMachineType type;
	ActiveStateMachineData data;

	uint8_t dead;
	uint8_t offscreenproc;

} ActiveStateMachine;

typedef Tile Map[WORLD_SIZE_X][WORLD_SIZE_Y];

typedef struct {
	char *base_path;
	Map map;

	ActiveStateMachine *activeTiles;
	size_t activeTileCount;
	
	Camera2D camera;

	Resources res;

	Coord currentSelected;
	uint8_t frameOfset;

} World;

#define countof(ARRAY) sizeof(ARRAY)/sizeof(ARRAY[0])
