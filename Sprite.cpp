#include "Sprite.h"

Sprite::Sprite() {
	cout << this << "Sprite created " << "EMPTY" << ' ' << endl;
}

Sprite::~Sprite() {
	cout << this << " Sprite destroyed " << ID << ' ' << endl;
}

Sprite::Sprite(SDL_Texture * _texture, double x, double y, int w, int h,
	int _pwsheet, int _phsheet, int _fwsheet, int _fhsheet)
	: texture(_texture), pwsheet(_pwsheet), phsheet(_phsheet), fwsheet(_fwsheet), fhsheet(_fhsheet) {
	ID = ++count;
	rect.w = w;
	rect.h = h;
	rect.x = x - w/2;
	rect.y = y - w/2;
	
	sect.w = pwsheet/fwsheet;
	sect.h = phsheet/fhsheet;
	sect.x = 0;
	sect.y = 0;
	cout << this << " Sprite created " << ID << ' '  << endl;
}

unsigned int Sprite::count = -1;