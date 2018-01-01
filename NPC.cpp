#include "NPC.h"


NPC::NPC() {
	cout << this << " NPC " << "EMPTY" << ' ' << endl;
}

NPC::~NPC() {
	for (auto it = NPC::nvec.begin(); it != NPC::nvec.end();)
		if ((*it)->getID() == getID())
			it = NPC::nvec.erase(it);
		else
			++it;
	for (auto it = Object::ovec.begin(); it != Object::ovec.end();)
		if ((*it)->getID() == getID()) {
			it = Object::ovec.erase(it);
		}
		else
			++it;

	cout << this << " NPC destroyed " << ID << endl;
}

/*
typedef vector<pair<const char, Playable *>> KCOMMAND;
typedef vector<const string, KCOMMAND> KMAP;
*/

NPC::NPC(SDL_Texture * _texture, double x, double y, int w, int h,
	int _pwsheet, int _phsheet, int _fwsheet, int _fhsheet)
	: Object(_texture, x, y, w, h, NULL, _pwsheet, _phsheet, _fwsheet, _fhsheet), origin(position), destination(origin),
	Stats(5), aggro(false) {
	addVec();
	cout << this << " NPC " << ID << " origin: X " << origin.first << " Y " << origin.second << endl;
}

void NPC::addVec() {
	nvec.push_back(this);
}



void NPC::AI(const unsigned int& t_past, Playable * player) {
	if (aggro) {
		destination = player->readPosition();
	} else {
		double distance = sqrt(pow((destination.first - position.first), 2) + pow((destination.second - position.second), 2));
		if (distance < 10)
		{
			double angle = (rand() % (int)(2 * PI * 1000)) / 1000;
			destination.first = cos(angle)*MAX_DISTANCE + origin.first;
			destination.second = sin(angle)*MAX_DISTANCE + origin.second;

			accel.first = 0;
			accel.second = 0;
		}
		else {
			if (destination.first < 0)
				destination.first = 0 + rect.w / 2;
			else if (destination.first > WindowUtil::SCREEN_WIDTH)
				destination.first = WindowUtil::SCREEN_WIDTH - rect.w / 2;

			if (destination.second < 0)
				destination.second = 0 + rect.w / 2;
			else if (destination.second > WindowUtil::SCREEN_HEIGHT)
				destination.second = WindowUtil::SCREEN_HEIGHT - rect.w / 2;



		}
	}
	//set accel
	if ((destination.first - position.first) > 0)
		accel.first = 3 * pow((destination.first - position.first), .000001);
	else
		accel.first = -3 * pow(abs(destination.first - position.first), .000001);
	if ((destination.second - position.second > 0))
		accel.second = 3 * pow((destination.second - position.second), .000001);
	else
		accel.second = -3 * pow(abs(destination.second - position.second), .000001);
}

NVEC NPC::nvec;