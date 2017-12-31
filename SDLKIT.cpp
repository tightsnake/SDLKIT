#include "SDLKIT.h"

SDLKIT::SDLKIT() : tpack("Textures.txt",renderer), running(true), controller(0b0000000000000000) {
	srand(time(NULL));
	cout << this << " SDLKIT Constructed\n";
}

SDLKIT::~SDLKIT() {
	cout << "\n\t" << this << " SDLKIT Destructing\n";
	Object::deleteAll();
}

void SDLKIT::drawObjects() {
	SDL_RenderClear(renderer);

	viewport.x = (player->readPosition().first - (SCREEN_WIDTH / 2));
	viewport.y = (player->readPosition().second - (SCREEN_HEIGHT / 2));

	if (viewport.x < 0)
		viewport.x = 0;
	if (viewport.y < 0)
		viewport.y = 0;

	if (viewport.x + viewport.w >= WIDTH_MAX)
		viewport.x = WIDTH_MAX - SCREEN_WIDTH;
	if (viewport.y + viewport.h  >= HEIGHT_MAX)
		viewport.y = HEIGHT_MAX - SCREEN_HEIGHT;

	//reverse iterate so that the player is on the top of the stack.
	for (auto it = Object::ovec.begin(); it != Object::ovec.end(); ++it)
	{
		//first we need to only print things in the viewport...
		SDL_Rect drawRect = { (*it)->getRect().x - viewport.x, (*it)->getRect().y - viewport.y,
		(*it)->getRect().w, (*it)->getRect().h };
		//SPRITE RECT
		SDL_RenderCopyEx(renderer, (*it)->getTexture(), &(*it)->getSect(), &drawRect,(*it)->readAngle()*(180/PI),NULL,SDL_FLIP_NONE);
	}
	SDL_RenderPresent(renderer);
}

/*
/////////////////////////////////////////////////////
This is basically the keybinding for the game/module.
*/

//Using a binary 16 bit uint - by each associated bit, mapped key assigned:
//0 0 0 0 0 0 0 0 0 0 0 SHIFT D A S W

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

	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
		//cout << "XAccel 0\n";
		controller = controller | 0b10000;
		break;

	default:
		break;
	}

	cout << bitset<8>(controller) << endl;
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

	case SDLK_LSHIFT:
	case SDLK_RSHIFT:
		//cout << "XAccel 0\n";
		controller = (controller & ~(0b10000));
		break;

	default:
		break;
	}

	cout << bitset<8>(controller) << endl;
}

void SDLKIT::dispatchMouseUpRight(const SDL_Keycode & keycode) {

}

void SDLKIT::dispatchMouseUpLeft(const SDL_Keycode & keycode) {

}

void SDLKIT::dispatchMouseDownRight(const SDL_Keycode & keycode) {

}

void SDLKIT::dispatchMouseDownLeft(const SDL_Keycode & keycode) {
	SDL_Point mouse_position;

	SDL_GetMouseState(                    //    Sets mouse_position to...
		&mouse_position.x,                // ...mouse arrow coords on window
		&mouse_position.y
	);

	double y = (mouse_position.y + viewport.y) - player->readPosition().second;
	double x = (mouse_position.x + viewport.x) - player->readPosition().first;

	double angle = atan(y / x);
	if (x < 0)
		angle += PI;
	cout << "Angle : " << angle << " radians - XY: " << x << ' ' << y << '\n';
	COORD velvec(0.0, 0.0);
	velvec.first = cos(angle) * 40;
	velvec.second = sin(angle) * 40;

	(new Object(tpack.getTexture("arrow.png"), player->readPosition().first, player->readPosition().second,
		64, 16, angle, 64, 16))->setVelocity(velvec).addPVec();

}

bool collision(Object * projectile, Object * npc) {
	return (projectile->readPosition().first >= npc->getRect().x &&
		projectile->readPosition().first <= npc->getRect().x + npc->getRect().w &&
		projectile->readPosition().second >= npc->getRect().y &&
		projectile->readPosition().second <= npc->getRect().y + npc->getRect().h);
}

//SIN WAV COIN.

void SDLKIT::processKeys() {
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

	if (controller & 0b10000)
		player->setXAccel(0).setYAccel(0).setVelocity(COORD(0, 0));
}

void SDLKIT::process() {
	processKeys();

	// This is how we can get the time past between processing data, and
	// will be used to pass to associated functions that are time dependent.
	t_current = SDL_GetTicks();
	unsigned int t_past = t_current - t_last;
	t_last = t_current;

	for (auto& npc : NPC::nvec) {
		npc->AI(t_past, player);
		for (auto& projectile : Object::opvec) {
			if (collision(projectile, npc)) {
				npc->setVelocity(COORD(npc->readVelocity().first + projectile->readVelocity().first / 5,
					npc->readVelocity().second + projectile->readVelocity().second / 5));
				for (auto it = Object::opvec.begin(); it != Object::opvec.end();)
					if ((*it)->getID() == projectile->getID())
						it = Object::opvec.erase(it);
					else
						++it;
				for (auto it = Object::ovec.begin(); it != Object::ovec.end();)
					if ((*it)->getID() == projectile->getID())
						it = Object::ovec.erase(it);
					else
						++it;
				delete projectile;
				npc->dealDamage(1);
			}
		}
	}
		for (auto it = NPC::nvec.begin(); it != NPC::nvec.end();){
			if ((*it)->getHP() <= 0) {
				for (auto oit = Object::ovec.begin(); oit != Object::ovec.end();)
					if ((*oit)->getID() == (*it)->getID()) {
						oit = Object::ovec.erase(oit);
					}
					else
						++oit;
				delete (*it);
				it = NPC::nvec.erase(it);
			}
			else
				++it;
	}
	//Positions
	//player->setVelocity(t_past).setPosition();
	//Thank god for OOP and return types of reference&
	for (auto& obj : Object::ovec)
		obj->setVelocity(t_past).setFrame(t_past).setPosition();

}

void SDLKIT::mainLoop() {
	//
	//THIS IS WHERE TEST CODE CAN GO:
	new Object(tpack.getTexture("dirt.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, WIDTH_MAX + WindowUtil::SCREEN_WIDTH, HEIGHT_MAX + WindowUtil::SCREEN_HEIGHT, NULL,
		96, 96, 1, 1);

	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH, WindowUtil::SCREEN_HEIGHT, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH, WindowUtil::SCREEN_HEIGHT, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH, WindowUtil::SCREEN_HEIGHT, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH, WindowUtil::SCREEN_HEIGHT, 192, 256, 192, 256, 4, 4);
	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH, WindowUtil::SCREEN_HEIGHT, 192, 256, 192, 256, 4, 4);

	new NPC(tpack.getTexture("goblin.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, 192, 256, 192, 256, 4, 4);

	player = new Playable(tpack.getTexture("julia.png"), WindowUtil::SCREEN_WIDTH / 2, WindowUtil::SCREEN_HEIGHT / 2, 128, 128, 128, 128, 4, 4);
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
				if(event.button.button == SDL_BUTTON_RIGHT)
				dispatchMouseDownRight(event.key.keysym.sym);
				if (event.button.button == SDL_BUTTON_LEFT)
				dispatchMouseDownLeft(event.key.keysym.sym);
				break;
			}
			if (event.type == SDL_MOUSEBUTTONUP) {
				//cout << "-\n";
				if (event.button.button == SDL_BUTTON_RIGHT)
				dispatchMouseUpRight(event.key.keysym.sym);
				if (event.button.button == SDL_BUTTON_LEFT)
				dispatchMouseUpLeft(event.key.keysym.sym);
				break;
			}
		}
		process();
		drawObjects();
	}
}
