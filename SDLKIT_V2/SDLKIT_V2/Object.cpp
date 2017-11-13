#include "Object.h"

Object::Object() {
	cout << this << " Object created " << "EMPTY" << ' ' << endl;
};

Object::Object(SDL_Texture * _texture, double x, double y, int w, int h)
	: Sprite(_texture, x, y, w, h), collidable(true), accel(0, 0), velocity(0, 0),  position(x, y){
	addVec();
	cout << this << " Object created " << ID << ' ' << endl;
}

Object::~Object() {
	cout << this << " Object destroyed " << ID << ' ' << endl;
}

void Object::addVec() {
	ovec.push_back(this);
};

void Object::deleteAll() {
	for (auto it = ovec.begin(); it != ovec.end();)
	{
		if (*it != nullptr)
			delete *it;
		it = ovec.erase(it);
	}
}

Object& Object::setVelocity(const unsigned int& t_past) {
	//Use acceleration off gravity
	//v = v0 + at
	velocity.second = velocity.second + (Y_GRAVITY - accel.second) * ((double)t_past / 1000);
	velocity.first = velocity.first + (X_GRAVITY + accel.first) * ((double)t_past / 1000);
	return *this;
}
Object& Object::setPosition() {
	position.first += velocity.first;
	position.second += velocity.second;
	rect.x += velocity.first;
	rect.y += velocity.second;
	return *this;
}
void Object::reboundX() {
	velocity.first = -velocity.first * KINETIC_FRICTION;
}
void Object::reboundY() {
	velocity.second = -velocity.second * KINETIC_FRICTION;
}

double Object::Y_GRAVITY = X_GRAV;
double Object::X_GRAVITY = Y_GRAV;
//Z Gravity for the dimension of friction on a 2D Surface.
double Object::Z_GRAVITY = Z_GRAV;

OVEC Object::ovec;