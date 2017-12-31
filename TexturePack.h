#pragma once
#include "SDL.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include "SDL_image.h"

using namespace std;

typedef pair<string, SDL_Texture *> TPAIR;
typedef vector<TPAIR> TVEC;
class TexturePack {
public:
	TexturePack(const string& tpath, SDL_Renderer * renderer);

	~TexturePack();

	//Critical memory function: Destroy Textures.
	void T_Destroy();

	bool T_Initialize(const string& tpath, SDL_Renderer * renderer);

	SDL_Texture * getTexture(const string& tname);

protected:
	TVEC tvec;
private:
	ifstream ifs;
};