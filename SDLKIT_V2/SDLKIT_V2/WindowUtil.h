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
};