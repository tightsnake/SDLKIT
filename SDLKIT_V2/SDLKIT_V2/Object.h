#pragma once
#include "Sprite.h"

#define X_GRAV 0
#define Y_GRAV 10
#define Z_GRAV 0
#define STATIC_FRICTION 0.8
#define KINETIC_FRICTION 0.6

class Object;

typedef pair<double, double> COORD;
typedef vector<Object*> OVEC;
class Object : public Sprite {
public:
	//Consctructor methods.
	Object();
	virtual ~Object();
	Object(SDL_Texture * _texture, double x, double y, int w, int h);
	//Data management methods.
	void addVec();
	static void deleteAll();
	//Object methods.
	//These can be chain invoked because they return a reference to the currenct object.
	Object& setVelocity(const unsigned int& t_past);
	Object& setPosition();

	const COORD& readVelocity() { return velocity; }

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

protected:
	static double Y_GRAVITY;
	static double X_GRAVITY;
	static double Z_GRAVITY;
	bool collidable;
	COORD accel, velocity, position;
};
