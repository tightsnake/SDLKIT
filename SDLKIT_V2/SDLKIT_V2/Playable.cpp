#include "Playable.h"

Playable::Playable() {
	cout << this << " Playable created " << "EMPTY" << ' ' << endl;
}

Playable::Playable(SDL_Texture * _texture, double x, double y, int w, int h, const string& _keyset) 
: Object(_texture, x, y, w, h), keyset(_keyset) {
	cout << this << " Playable created " << ID << ' ' << endl;
}