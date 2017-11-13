#include "WindowUtil.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

WindowUtil::WindowUtil() {
	if (SDL_Initialize())
		cout << '\t' << this << " WindowUtil constructed\n";
	else
		cout << '\t' << this << " WindowUtil failed to construct\n";
}

WindowUtil::~WindowUtil() {
	cout << '\t' << this << " Destroying WindowUtil "  << ':' << endl;

	cout << renderer << " Renderer" << endl;
	SDL_DestroyRenderer(renderer);

	cout << window << " Window "  << endl;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool WindowUtil::SDL_Initialize() {
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		cout << "SDL_Init Error.\n";
		return false;
	}

	window = SDL_CreateWindow("Window",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << "SDL_CreateWindow Error.\n";
		SDL_Quit();
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		SDL_DestroyWindow(window);
		cout << "SDL_CreateRenderer Error.\n" << SDL_GetError() << endl;
		SDL_Quit();
		return false;
	}
	return true;
}