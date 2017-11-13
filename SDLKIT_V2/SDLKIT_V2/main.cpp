#include "SDLKIT.h"

int main(int argc, char * argv[]) {
	system("Color 0A");
	SDLKIT * sdlkit = new SDLKIT;

	int x;

	sdlkit->mainLoop();
	delete sdlkit;

	cin >> x;

	return 0;
}