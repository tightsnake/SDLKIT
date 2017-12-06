#pragma once
#include "Object.h"

class Playable : public Object {
public:
	Playable();
	virtual ~Playable();
	Playable(SDL_Texture * _texture, double x, double y, int w, int h);
protected:
};