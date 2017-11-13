#pragma once
#include "Object.h"

class Playable : public Object {
public:
	Playable();
	Playable(SDL_Texture * _texture, double x, double y, int w, int h, const string& _keyset);
protected:
	string keyset;
};