#pragma once
#include "Sprite.h"
#include <math.h>

#define X_GRAV 10
#define Y_GRAV 10
#define Z_GRAV 10

#define STATIC_FRICTION 0.8
#define KINETIC_FRICTION 0.3

#define FRAME_TIMER 50.0

class Object;

typedef pair<double, double> COORD;
typedef vector<Object*> OVEC;
class Object : public Sprite {
public:
	//Consctructor methods.
	Object();
	virtual ~Object();
	Object(SDL_Texture * _texture, double x, double y, int w, int h, double _angle = 0,
		int _pwsheet = 1, int _phsheet = 1, int _fwsheet = 1, int _fhsheet = 1);
	//Data management methods.
	void addVec();
	void addPVec();
	static void deleteAll();

	//Object methods.
	//These can be chain invoked because they return a reference to the currenct object.
	Object& setXAccel(const double& val);
	Object& setYAccel(const double& val);
	Object& setVelocity(const unsigned int& t_past);
	Object& setVelocity(const COORD& vel);
	Object& setPosition();

	Object& setFrame(const unsigned int& t_past);

	const COORD& readPosition() { return position; }
	const COORD& readVelocity() { return velocity; }
	const COORD& readAccel() { return accel; }

	const double& readAngle() { return angle; }

	void reboundX();
	void reboundY();
	
	bool isCol() { return collidable; }

	static void setYGravity(const double& gravity) { Y_GRAVITY = gravity; }
	static const double& getYGravity() { return Y_GRAVITY; }

	static void setXGravity(const double& gravity) { X_GRAVITY = gravity; }
	static const double& getXGravity() { return X_GRAVITY; }

	static void setZGravity(const double& gravity) { Z_GRAVITY = gravity; }
	static const double& getZGravity() { return Z_GRAVITY; }

	static OVEC ovec;
	static OVEC opvec;

protected:
	static double Y_GRAVITY;
	static double X_GRAVITY;
	static double Z_GRAVITY;

	double angle;

	bool collidable;

	COORD accel, velocity, position;

	unsigned int frametimer;
};
