#pragma once
#include "WindowUtil.h"
#include "TexturePack.h"
#include "Playable.h"
#include <iostream>
#include <utility>
#include <vector>
#include <map>

using namespace std;

typedef map<SDL_Keycode,vector<void *>> keymap;
class KEYMAP {
public:
	KEYMAP() { cout << "\t" << this << " KEYMAP Constructed\n"; }
	~KEYMAP() { cout << "\t" << this << " KEYMAP Destroyed\n"; }

	void add(const SDL_Keycode & keycode, Object * object) {
		keymap[keycode].push_back(&object);
	}

private:
	keymap keymap;
};

class SDLKIT : public WindowUtil {
public:
	SDLKIT();
	~SDLKIT();

	void drawObjects();

	void dispatchKeyUp(const SDL_Keycode & keycode);

	void dispatchKeyDown(const SDL_Keycode & keycode);

	void mainLoop();

protected:
	TexturePack tpack;
	bool running;
	SDL_Event event;
	SDL_Texture * textfield;
	char * text;
	char * composition;
	Sint32 cursor;
	Sint32 selection_len;
};