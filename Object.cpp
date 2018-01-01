#include "Object.h"

Object::Object() {
	cout << this << " Object created " << "EMPTY" << ' ' << endl;
};

Object::Object(SDL_Texture * _texture, double x, double y, int w, int h, double _angle,
	int _pwsheet, int _phsheet, int _fwsheet, int _fhsheet)
	: Sprite(_texture, x, y, w, h, _pwsheet, _phsheet, _fwsheet, _fhsheet),
	collidable(true), accel(0, 0), velocity(0, 0), position(x, y), angle(_angle), frametimer(0) {
	addVec();
	cout << this << " Object created " << ID << ' ' << endl;
}

Object::~Object() {
	//When an Object destructs, it should automatically remove itself from all vectors.
	//This is actually the solution to the projectile bug!
	for (auto it = Object::opvec.begin(); it != Object::opvec.end();)
		if ((*it)->getID() == getID())
			it = Object::opvec.erase(it);
		else
			++it;

	for (auto it = Object::ovec.begin(); it != Object::ovec.end();)
		if ((*it)->getID() == getID()) {
			it = Object::ovec.erase(it);
		}
		else
			++it;

	cout << this << " Object destroyed " << ID << ' ' << endl;
}

void Object::addVec() {
	ovec.push_back(this);
};

void Object::addPVec() {
	opvec.push_back(this);
};

void Object::deleteAll() {
	while (ovec.size() > 0) {
		delete ovec.at(0);
	}
}

Object& Object::setXAccel(const double& val) {
	accel.first = val;
	return *this;
}

Object& Object::setYAccel(const double& val) {
	accel.second = val;
	return *this;
}

Object& Object::setVelocity(const unsigned int& t_past) {
	//Use acceleration
	////v = v0 + at
	//cout << t_past << " ms -\n";
	velocity.second = (velocity.second + ((accel.second) * (double)t_past / 1000));
	velocity.first = (velocity.first + ((accel.first) * (double)t_past / 1000));
	//cout << accel.first << ' ' << accel.second << endl;
	//cout << "X: " << velocity.first << " Y: " << velocity.second << "\n-\n";
	velocity.first = (velocity.first) * (pow((double)KINETIC_FRICTION, (double)t_past / 1000));
	velocity.second = (velocity.second) * (pow((double)KINETIC_FRICTION, (double)t_past / 1000));
	//cout << "X: " << velocity.first << " Y: " << velocity.second << "\n-\n";
	return *this;
}

Object& Object::setVelocity(const COORD& vel) {
	velocity.first = vel.first;
	velocity.second = vel.second;
	return *this;
}

//Rectangle is being lame as fuck because it uses integers - messes up physics math.
Object& Object::setPosition() {
	position.first += velocity.first;
	position.second += velocity.second;

	if (position.first < 0)
		position.first = 0;
	if (position.second < 0)
		position.second = 0;

	if (position.first >= WindowUtil::WIDTH_MAX)
		position.first = WindowUtil::WIDTH_MAX;
	if (position.second >= WindowUtil::HEIGHT_MAX)
		position.second = WindowUtil::HEIGHT_MAX;

	rect.x = position.first - rect.w / 2;
	rect.y = position.second - rect.h / 2;
	return *this;
}

Object& Object::setFrame(const unsigned int& t_past) {

	//ONLY DO THIS IF NOT IDLE i.e. MAG VEL > ~ 0
	if (!(abs(velocity.first) < 0.3 && abs(velocity.second) < 0.3) && fwsheet > 1 && fhsheet > 1) {
		frametimer += t_past;
		if (frametimer >= (FRAME_TIMER * pow(5,(1/(1 + sqrt(pow(velocity.first,2) + pow(velocity.second,2))))))) {
			frametimer = 0;
			sect.x += sect.w;
			if (sect.x >= pwsheet)
				sect.x = 0;
		}
		if (velocity.first > 0)
			if (velocity.first >= abs(velocity.second))
				sect.y = 2 * sect.h;
			else
				if (velocity.second > 0)
					sect.y = 0;
				else
					sect.y = 3 * sect.h;
		else
			if (abs(velocity.first) >= abs(velocity.second))
				sect.y = sect.h;
			else
				if (velocity.second > 0)
					sect.y = 0;
				else
					sect.y = 3 * sect.h;
	}
	else if(fwsheet > 1) {
		sect.x = sect.w;
	}
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
OVEC Object::opvec;