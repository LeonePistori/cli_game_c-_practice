#pragma once

#include<Entity.h>

#ifndef DIRECTIONS
#define DIRECTIONS
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#endif

#ifndef BOARD_SIZE
#define BOARD_SIZE 10
#endif

class Player : public Entity {
public:

	Player()
	{
		x = 0;
		y = 0;
		type = "PLAYER";
	}

	bool Move(int direction) {
		if (direction == DOWN) {
			if (y < BOARD_SIZE - 1) y++;
			else return false;
		}
		else if (direction == RIGHT) {
			if (x < BOARD_SIZE - 1) x++;
			else return false;
		}
		else if (direction == LEFT) {
			if (x > 0) x--;
			else return false;
		}
		else if (direction == UP) {
			if (y > 0) y--;
			else return false;
		}
		else return false;
		return true;
	}

	bool Damage(int damage) {
		health = health - damage;
		if (health < 1) {
			return true;
		}
		else false;
	}
};