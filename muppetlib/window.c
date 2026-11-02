#include "window.h"

void init() {
	SetTraceLogLevel(LOG_ERROR);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	SetTargetFPS(60);
	InitWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, GAME_NAME);

	printf("init\n");
}

uint16_t shouldQuit() {
	return WindowShouldClose();
}

void quit() {
	CloseWindow();
}

void toggleFullScreen() {
	static int windowWidth = 0;
	static int windowHeight = 0;

	if (IsWindowFullscreen()) {
		ToggleFullscreen();
		SetWindowSize(windowWidth, windowHeight);
	} else {
		windowWidth = GetScreenWidth();
		windowHeight = GetScreenHeight();
		
		int monitor = GetCurrentMonitor();
		SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
		ToggleFullscreen();
	}
}
