#include "Sprite.h"

Sprite::Sprite() {
	cout << this << "Sprite created " << "EMPTY" << ' ' << endl;
}

Sprite::~Sprite() {
	cout << this << " Sprite destroyed " << ID << ' ' << endl;
}

Sprite::Sprite(SDL_Texture * _texture, double x, double y, int w, int h)
	: texture(_texture) {
	ID = ++count;
	rect.w = w;
	rect.h = h;
	rect.x = x - w/2;
	rect.y = y - w/2;
	cout << this << " Sprite created " << ID << ' '  << endl;
}

unsigned int Sprite::count = -1;