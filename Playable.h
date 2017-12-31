#pragma once
#include "Object.h"
#include "Stats.h"

class Playable : public Object, public Stats {
public:
	Playable();
	virtual ~Playable();
	Playable(SDL_Texture * _texture, double x, double y, int w, int h,
		int _pwsheet = 1, int _phsheet = 1, int _fwsheet = 1, int _fhsheet = 1);
protected:
};