#include "Effect.h"

Effect::Effect() {
	cout << this << " Effect constructed " << ID << endl;
}

Effect::~Effect() {
	for (auto it = Effect::evec.begin(); it != Effect::evec.end();)
		if ((*it)->getID() == getID())
			it = Effect::evec.erase(it);
		else
			++it;

	for (auto it = Object::ovec.begin(); it != Object::ovec.end();)
		if ((*it)->getID() == getID())
			it = Object::ovec.erase(it);
		else
			++it;

	cout << this << " Effect destroyed " << ID << endl;
}

Effect::Effect(SDL_Texture * _texture, double x, double y, int w, int h, long time,
	int _pwsheet, int _phsheet, int _fwsheet, int _fhsheet)
		: Object(_texture, x, y, w, h, 0, _pwsheet, _phsheet, _fwsheet, _fhsheet), limit(time), timer(0) {

	ratio = limit / _fwsheet;
	addVec();
	cout << this << " Effect constructed " << ID << endl;
}

void Effect::addVec() {
	evec.push_back(this);
}

bool Effect::decay(const unsigned int& t_past){
	timer += t_past;

	//If the timer has expired, it's time to be destroyed.
	if (timer >= limit)
		return true;

	//If we didn't return, then we have to determine what frame we are on.
	sect.x = timer / ratio * sect.w;
	return false;
}

EVEC Effect::evec;