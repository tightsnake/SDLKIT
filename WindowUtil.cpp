#include "WindowUtil.h"


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

	SDL_DisplayMode dm;

	if (SDL_GetDesktopDisplayMode(0, &dm) != 0)
	{
		//SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
		cout << "SDL_GetDesktopDisplayMode failed: %s" << SDL_GetError() << endl;
		return false;
	}

	SCREEN_WIDTH = dm.w;
	SCREEN_HEIGHT = dm.h;
	WIDTH_MAX = SCREEN_WIDTH * 2;
	HEIGHT_MAX = SCREEN_HEIGHT * 2;
	viewport.w = SCREEN_WIDTH;
	viewport.h = SCREEN_HEIGHT;

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

unsigned int WindowUtil::SCREEN_WIDTH = 0;
unsigned int WindowUtil::SCREEN_HEIGHT = 0;

unsigned int WindowUtil::WIDTH_MAX;
unsigned int WindowUtil::HEIGHT_MAX;