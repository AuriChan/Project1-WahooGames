#pragma once

//game size 
#define GAME_SCALE_FACTOR	4.0f
#define WINDOW_WIDTH    254
#define WINDOW_HEIGHT   214 //198
#define MARGIN_GUI_Y	28
#define TILE_SIZE		16
#define LEVEL_WIDTH		25
#define LEVEL_HEIGHT	17
#define ANIM_DELAY		4

//App performance parameters
enum class AppStatus { OK = 0, ERROR, QUIT };
#define EXIT_SUCCESS	0
#define EXIT_FAILURE	1

//Log messages
#define LOG(text, ...) log(__FILE__, __LINE__, text, __VA_ARGS__);
void log(const char file[], int line, const char* text, ...);


