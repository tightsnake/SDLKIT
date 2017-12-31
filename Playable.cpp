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

Playable::Playable(SDL_Texture * _texture, double x, double y, int w, int h,
	int _pwsheet, int _phsheet, int _fwsheet, int _fhsheet)
	: Object(_texture, x, y, w, h, 0, _pwsheet, _phsheet, _fwsheet, _fhsheet), Stats(10) {
	cout << this << " Playable created " << ID << endl;
}