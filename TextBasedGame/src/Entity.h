#pragma once

class Entity{
public:
	int x, y;
	int health;
	int damage;
	const char* type;

	Entity() 
	: health(3), damage(1)
	{}

	virtual bool Move(int direction) {
		return true;
	}

	virtual bool Damage(int damage) {
		return true;
	}
};