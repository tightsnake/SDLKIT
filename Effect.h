#pragma once

#include "Object.h"

class Effect;
typedef vector<Effect*> EVEC;
class Effect : public Object {
public:
	Effect();
	virtual ~Effect();
	Effect(SDL_Texture * _texture, double x, double y, int w, int h, long time,
		int _pwsheet = 1, int _phsheet = 1, int _fwsheet = 1, int _fhsheet = 1);
	static EVEC evec;
	void addVec();
	bool decay(const unsigned int& t_past);
private:
	unsigned long limit, timer;
	int ratio;
};