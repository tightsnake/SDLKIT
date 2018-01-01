#pragma once
#include "SDL.h"
#include "WindowUtil.h"
#include <vector>
#include <utility>
#include <iostream>

#define PI 3.14159265359

#define S_WIDTH 16
#define S_HEIGHT 16

using namespace std;

class Sprite {
public:
	Sprite();
	virtual ~Sprite();
	Sprite(SDL_Texture * _texture, double x, double y, int w, int h,
		int _pwsheet = 1, int _phsheet = 1, int _fwsheet = 1, int _fhsheet = 1);
	const unsigned int& getID() { return ID; }
	SDL_Texture * getTexture() { return texture; }
	SDL_Rect& getRect() { return rect; }
	SDL_Rect& getSect() { return sect; }
protected:
	static unsigned int count;
	unsigned int ID;
	SDL_Rect rect, sect;
	SDL_Texture * texture;
	int pwsheet, phsheet, fwsheet, fhsheet;
};
