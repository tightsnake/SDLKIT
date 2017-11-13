#pragma once
#include "SDL.h"
#include <vector>
#include <utility>
#include <iostream>

#define S_WIDTH 16
#define S_HEIGHT 16

using namespace std;

class Sprite {
public:
	Sprite();
	virtual ~Sprite();
	Sprite(SDL_Texture * _texture, double x, double y, int w, int h);
	const unsigned int& getID() { return ID; }
	SDL_Texture * getTexture() { return texture; }
	SDL_Rect& getRect() { return rect; }
protected:
	static unsigned int count;
	unsigned int ID;
	SDL_Rect rect;
	SDL_Texture * texture;
};
