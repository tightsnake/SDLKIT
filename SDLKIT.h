#pragma once
#include "WindowUtil.h"
#include "TexturePack.h"
#include "Playable.h"
#include "NPC.h"
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <bitset>
#include <time.h>

using namespace std;

//Deprecated
typedef unordered_map<SDL_Keycode, bool> KEYMAP;
//End Deprecated

//Using binary operators - quickest way to interact with hardware.
typedef uint16_t ControlSet;

class SDLKIT : public WindowUtil {
public:
	SDLKIT();
	~SDLKIT();

	void dispatchKeyDown(const SDL_Keycode & keycode);

	void dispatchKeyUp(const SDL_Keycode & keycode);

	void dispatchMouseUpRight(const SDL_Keycode & keycode);

	void dispatchMouseUpLeft(const SDL_Keycode & keycode);

	void dispatchMouseDownRight(const SDL_Keycode & keycode);

	void dispatchMouseDownLeft(const SDL_Keycode & keycode);

	void processKeys();

	void process();

	void drawObjects();

	void mainLoop();

protected:
	//Deprecated
	KEYMAP keymap;
	//End Deprecated

	ControlSet controller;
	//Using a binary 16 bit uint - by each associated bit, mapped key assigned:
	//0 0 0 0 0 0 0 0 0 0 0 0 D A S W
	TexturePack tpack;
	bool running;
	SDL_Event event;
	Playable * player;
	unsigned int t_last = 0, t_current;
};