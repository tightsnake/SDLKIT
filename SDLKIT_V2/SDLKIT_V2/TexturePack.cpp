#include "TexturePack.h"

TexturePack::TexturePack(const string& tpath, SDL_Renderer * renderer) {
	if (T_Initialize(tpath, renderer))
		cout << '\t' << this << " TexturePack constructed\n";
	else
		cout << '\t' << this << " TexturePack failed to construct\n";
}

TexturePack::~TexturePack() {
	cout << '\t' << this << " Destroying TexturePack " << ':' << endl;
	T_Destroy();
}

//Critical memory function: Destroy Textures.
void TexturePack::T_Destroy() {
	for (auto it = tvec.begin(); it != tvec.end();) {
		cout << it->second << " Texture " << it->first << ' ' << endl;
		if (it->second != nullptr)
			SDL_DestroyTexture(it->second);
		it = tvec.erase(it);
	}
}

bool TexturePack::T_Initialize(const string& tpath, SDL_Renderer * renderer) {
	ifs.open(tpath);
	if (!ifs) {
		cout << "Texture file failed to load.\n";
		return false;
	}
	//string .c_str() has great function
	for (string tname; getline(ifs, tname);) {
		//A great for loop for string/getline
		SDL_Surface * bmp = SDL_LoadBMP(tname.c_str());
		if (bmp == nullptr) {
			cout << "SDL_LoadBMP Error: " << tname << " " << SDL_GetError() << endl;
			ifs.close();
			return false;
		}

		SDL_Texture * texture = SDL_CreateTextureFromSurface(renderer, bmp);
		SDL_FreeSurface(bmp);
		if (texture == nullptr) {
			cout << "SDL_LoadTexture Error: " << tname << " " << SDL_GetError() << endl;
			ifs.close();
			return false;
		}
		tvec.push_back(TPAIR(tname, texture));
	}
	ifs.close();
	return true;
}

SDL_Texture * TexturePack::getTexture(const string& tname) {
	for (auto it = tvec.begin(); it != tvec.end(); ++it) {
		if (it->first == tname)
			return it->second;
	}
	return nullptr;
}