#include "Playable.h"

Playable::Playable() {
	cout << this << " Playable created " << "EMPTY" << ' ' << endl;
}

Playable::~Playable() {
	cout << this << " Playable destroyed " << ID << ' ' << endl;
}

/*
typedef vector<pair<const char, Playable *>> KCOMMAND;
typedef vector<const string, KCOMMAND> KMAP;
*/

Playable::Playable(SDL_Texture * _texture, double x, double y, int w, int h)
	: Object(_texture, x, y, w, h) {
	cout << this << " Playable created " << ID << endl;
}