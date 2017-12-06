#pragma once
#include "WindowUtil.h"
#include "TexturePack.h"
#include "Playable.h"
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <bitset>

#define PI 3.14159265359

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

	void dispatchMouseUp(const SDL_Keycode & keycode);

	void dispatchMouseDown(const SDL_Keycode & keycode);

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