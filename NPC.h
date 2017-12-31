#pragma once
#include "Playable.h"
#include "Object.h"
#include "Stats.h"

#define MAX_DISTANCE 3000.0

class NPC;

typedef vector<NPC*> NVEC;
class NPC : public Object , public Stats {
public:
	NPC();
	virtual ~NPC();
	NPC(SDL_Texture * _texture, double x, double y, int w, int h,
		int _pwsheet = 1, int _phsheet = 1, int _fwsheet = 1, int _fhsheet = 1);

	static NVEC nvec;

	void addVec();

	void AI(const unsigned int& t_past, Playable * player);
	
	void toggleAggro() { aggro = true; };

	bool isAggro() { return aggro; };

protected:
	COORD origin, destination;
	bool aggro;
};