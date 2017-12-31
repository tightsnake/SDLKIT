#pragma once
#include <iostream>
using namespace std;

class Stats {
public:
	Stats() { cout << this << " Stats constructed\n"; }
	Stats(const int& _hp) : hp(_hp) { cout << this << " Stats constructed\n"; }
	virtual ~Stats() { cout << this << " Stats destructed\n"; }

	bool dealDamage(const int& dmg) { 
		hp -= dmg;
		return (hp <= 0);
	}
	
	int getHP() { return hp; }
protected:
	int hp;
};