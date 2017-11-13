#include "SDLKIT.h"

SDLKIT::SDLKIT() : tpack("Textures.txt",renderer), running(true), text(new char[256]), composition(new char[256]) {
	cout << this << " SDLKIT Constructed\n";
}

SDLKIT::~SDLKIT() {
	cout << "\n\t" << this << " SDLKIT Destructing\n";
	Object::deleteAll();
	delete[] text, composition;
}

void SDLKIT::drawObjects() {
	SDL_RenderClear(renderer);
	for (auto it = Object::ovec.begin(); it != Object::ovec.end(); ++it)
	{
		SDL_RenderCopy(renderer, (*it)->getTexture(), NULL, &(*it)->getRect());
	}
	SDL_RenderPresent(renderer);
}

void SDLKIT::dispatchKeyUp(const SDL_Keycode & keycode) {

}

void SDLKIT::dispatchKeyDown(const SDL_Keycode & keycode) {
	//for each function associated with this key.
	//do the mapped function.
	
}

void SDLKIT::mainLoop() {
	//
	//THIS IS WHERE TEST CODE CAN GO:
	new Playable(tpack.getTexture("Rock.bmp"), 0, 0, 64, 64, "WASD");
	//

	SDL_StartTextInput();
	while (running) {
		//
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				running = false;
				break;
			}
			if (event.type == SDL_KEYDOWN) {
				dispatchKeyDown(event.key.keysym.sym);
				break;
			}
			if (event.type == SDL_KEYUP) {
				dispatchKeyUp(event.key.keysym.sym);
				break;
			}
			if (event.type == SDL_TEXTINPUT) {
				strcat(text, event.text.text);
				break;
			}
			if (event.type == SDL_TEXTEDITING) {
				composition = event.edit.text;
				cursor = event.edit.start;
				selection_len = event.edit.length;
				break;
			}
		}
		drawObjects();
	}
}