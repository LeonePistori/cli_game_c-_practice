#pragma once

#include<Entity.h>

class Enemy : public Entity {
public:

	Enemy() {
		health = 1;
		type = "ENEMY";
	}

	bool Damage(int damage) {
		health = health - damage;
		if (health < 1) {
			return true;
		}
		else false;
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
};