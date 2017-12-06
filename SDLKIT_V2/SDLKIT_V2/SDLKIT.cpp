#include "SDLKIT.h"

SDLKIT::SDLKIT() : tpack("Textures.txt",renderer), running(true), controller(0b0000000000000000) {
	cout << this << " SDLKIT Constructed\n";
}

SDLKIT::~SDLKIT() {
	cout << "\n\t" << this << " SDLKIT Destructing\n";
	Object::deleteAll();
}

void SDLKIT::drawObjects() {
	SDL_RenderClear(renderer);
	for (auto it = Object::ovec.begin(); it != Object::ovec.end(); ++it)
	{
		SDL_RenderCopyEx(renderer, (*it)->getTexture(), NULL, &(*it)->getRect(),(*it)->readAngle()*(180/PI),NULL,SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

/*
/////////////////////////////////////////////////////
This is basically the keybinding for the game/module.
*/

//Using a binary 16 bit uint - by each associated bit, mapped key assigned:
//0 0 0 0 0 0 0 0 0 0 0 0 D A S W

void SDLKIT::dispatchKeyDown(const SDL_Keycode & keycode) {
	cout << "KeyDown\n";
	switch (keycode) {
	case SDLK_w:
		//cout << "YAccel 0\n";
		controller = controller | 0b1;
		break;

	case SDLK_s:
		//cout << "YAccel 0\n";
		controller = controller | 0b10;
		break;

	case SDLK_a:
		//cout << "XAccel 0\n";
		controller = controller | 0b100;
		break;

	case SDLK_d:
		//cout << "XAccel 0\n";
		controller = controller | 0b1000;
		break;

	default:
		break;
	}

	cout << bitset<16>(controller) << endl;
	//for each function associated with this key.
	//do the mapped function.	
}

//Using a binary 16 bit uint - by each associated bit, mapped key assigned:
//0 0 0 0 0 0 0 0 0 0 0 0 D A S W

void SDLKIT::dispatchKeyUp(const SDL_Keycode & keycode) {
	//for each function associated with this key.
	//do the mapped function.
	cout << "KeyUp\n";
	switch (keycode) {
	case SDLK_w:
		//cout << "YAccel 0\n";	
		controller = controller ^ 0b1;
		break;

	case SDLK_s:
		//cout << "YAccel 0\n";
		controller = controller ^ 0b10;
		break;

	case SDLK_a:
		//cout << "XAccel 0\n";
		controller = controller ^ 0b100;
		break;

	case SDLK_d:
		//cout << "XAccel 0\n";
		controller = controller ^ 0b1000;
		break;

	default:
		break;
	}

	cout << bitset<16>(controller) << endl;
}

void SDLKIT::dispatchMouseUp(const SDL_Keycode & keycode) {

}

void SDLKIT::dispatchMouseDown(const SDL_Keycode & keycode) {
	SDL_Point mouse_position;
	SDL_GetMouseState(                    //    Sets mouse_position to...
		&mouse_position.x,                // ...mouse arrow coords on window
		&mouse_position.y
	);
	double y = mouse_position.y - player->readPosition().second;
	double x = mouse_position.x - player->readPosition().first;
	double angle = atan(y / x);
	if (x < 0)
		angle += PI;
	cout << "Angle : " << angle << " radians - XY: " << x << ' ' << y << '\n';
	COORD velvec(0.0, 0.0);
	velvec.first = cos(angle) * 10;
	velvec.second = sin(angle) * 10;
	Object * o = new Object(tpack.getTexture("arrow.bmp"), player->readPosition().first + 8, player->readPosition().second + 8, 64, 16, angle);
	o->setVelocity(velvec);
}

void SDLKIT::process() {

	if (controller & 0b1)
		player->setYAccel(-Y_GRAV);
	else if (controller & 0b10)
		player->setYAccel(Y_GRAV);
	else
		player->setYAccel(0);

	if (controller & 0b100)
		player->setXAccel(-X_GRAV);
	else if (controller & 0b1000)
		player->setXAccel(X_GRAV);
	else
		player->setXAccel(0);
	// This is how we can get the time past between processing data, and
	// will be used to pass to associated functions that are time dependent.
	t_current = SDL_GetTicks();
	unsigned int t_past = t_current - t_last;
	t_last = t_current;
	player->setVelocity(t_past).setPosition();
	for (auto& obj : Object::ovec)
		obj->setVelocity(t_past).setPosition();
}

void SDLKIT::mainLoop() {
	//
	//THIS IS WHERE TEST CODE CAN GO:
	player = new Playable(tpack.getTexture("Rock.bmp"), 0, 0, 32, 32);
	//

	while (running) {
		//
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
			if (event.type == SDL_KEYDOWN) {
				//cout << "+\n";
				dispatchKeyDown(event.key.keysym.sym);
				break;
			}
			if (event.type == SDL_KEYUP) {
				//cout << "-\n";
				dispatchKeyUp(event.key.keysym.sym);
				break;
			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {
				//cout << "-\n";
				dispatchMouseDown(event.key.keysym.sym);
				break;
			}
			if (event.type == SDL_MOUSEBUTTONUP) {
				//cout << "-\n";
				dispatchMouseUp(event.key.keysym.sym);
				break;
			}
		}
		process();
		drawObjects();
	}
}
