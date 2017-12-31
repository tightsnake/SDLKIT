#pragma once
#include <iostream>
#include "SDL.h"

using namespace std;

class WindowUtil {
public:
	WindowUtil();
	virtual ~WindowUtil();
	bool SDL_Initialize();
	SDL_Window * window;
	SDL_Renderer * renderer;

	static unsigned int SCREEN_WIDTH;
	static unsigned int SCREEN_HEIGHT;

	static unsigned int WIDTH_MAX;
	static unsigned int HEIGHT_MAX;

	SDL_Rect viewport;
};