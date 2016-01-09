#ifndef _GAME_H
#define _GAME_H 1

#include <d3d9.h>
#include <d3dx9.h>
#include <dxerr.h>
#include <dsound.h>
#include <dinput.h>
#include <windows.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "dxgraphics.h"
#include "dxaudio.h"
#include "dxinput.h"

#define APPTITLE "Alone"

#define FULLSCREEN 0
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void Game_Run(HWND);
void Game_End(HWND);

#endif