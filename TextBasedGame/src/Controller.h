#pragma once

#include<Board.h>
#include<Player.h>
#include<Enemy.h>
#include<cmath>

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

class Controller {
public:
	Board board;
	Player player;
	Enemy enemies[2];

	void Init() {
		player.x = 2;
		player.y = 2;
		enemies[0].x = 3;
		enemies[0].y = 4;
		enemies[1].x = 7;
		enemies[1].y = 2;
		board.grid[2][2] = &player;
		board.grid[3][4] = &enemies[0];
		board.grid[7][2] = &enemies[1];
		board.PrintMenu();
	}

	bool CheckRange(int index) {
		if (enemies[index].y == player.y) {
			if (enemies[index].x == player.x + 1 || enemies[index].x == player.x - 1) return true;
		}
		if (enemies[index].x == player.x) {
			if (enemies[index].y == player.y + 1 || enemies[index].y == player.y - 1) return true;
		}
		return false;
	}

	void SetNewCoordinates(int direction, int* x, int* y) {
		if (direction == DOWN) {
			*x = player.x;
			*y = player.y + 1;
		}
		else if (direction == RIGHT) {
			*x = player.x + 1;
			*y = player.y;
		}
		else if (direction == UP) {
			*x = player.x;
			*y = player.y - 1;
		}
		else if (direction == LEFT) {
			*x = player.x - 1;
			*y = player.y;
		}
	}

	void SetNewEnemyCoordinates(int direction, int* x, int* y, int index) {
		if (direction == DOWN) {
			*x = enemies[index].x;
			*y = enemies[index].y + 1;
		}
		else if (direction == RIGHT) {
			*x = enemies[index].x + 1;
			*y = enemies[index].y;
		}
		else if (direction == UP) {
			*x = enemies[index].x;
			*y = enemies[index].y - 1;
		}
		else if (direction == LEFT) {
			*x = enemies[index].x - 1;
			*y = enemies[index].y;
		}
	}

	bool Move(int direction) {
		int new_x, new_y;
		int old_x = player.x;
		int old_y = player.y;
		SetNewCoordinates(direction, &new_x, &new_y);
		if (board.grid[new_x][new_y] == nullptr) {
			if (!player.Move(direction)) return false;
			else {
				board.grid[old_x][old_y] = nullptr;
				board.grid[new_x][new_y] = &player;
				return true;
			}
		}
		else return false;
	}

	bool MoveEnemy(int direction, int index) {
		int new_x, new_y;
		int old_x = enemies[index].x;
		int old_y = enemies[index].y;
		SetNewEnemyCoordinates(direction, &new_x, &new_y, index);
		if (board.grid[new_x][new_y] == nullptr) {
			if (!enemies[index].Move(direction)) return false;
			else {
				board.grid[old_x][old_y] = nullptr;
				board.grid[new_x][new_y] = &enemies[index];
				return true;
			}
		}
		else return false;
	}

	void EnemyMove() {
		int direction;
		for (int i = 0; i < 2; i++) {
			if (enemies[i].health > 0){
				if (CheckRange(i)) {
					player.Damage(enemies[i].damage);
				}
				else {
					if (abs(enemies[i].x - player.x) > abs(enemies[i].y - player.y)) {
						if ((rand() % 2) == 0) {
							if (enemies[i].x > player.x) direction = LEFT;
							else direction = RIGHT;
							MoveEnemy(direction, i);
						}
						else {
							if ((rand() % 4) == 0) direction = UP;
							else if ((rand() % 4) == 1) direction = RIGHT;
							else if ((rand() % 4) == 2) direction = DOWN;
							else direction = LEFT;
							MoveEnemy(direction, i);
						}
					}
					else {
						if ((rand() % 2) == 0) {
							if (enemies[i].y > player.y) direction = UP;
							else direction = DOWN;
							MoveEnemy(direction, i);
						}
						else {
							if ((rand() % 4) == 0) direction = UP;
							else if ((rand() % 4) == 1) direction = RIGHT;
							else if ((rand() % 4) == 2) direction = DOWN;
							else direction = LEFT;
							MoveEnemy(direction, i);
						}
					}
				}
			}
		}
	}

	bool SpawnEnemies() {
		if (enemies[0].health > 0 || enemies[1].health > 0) return false;
		while (true) {
			enemies[0].x = rand() % BOARD_SIZE;
			enemies[0].y = rand() % BOARD_SIZE;
			if (board.grid[enemies[0].x][enemies[0].y] == nullptr) {
				board.grid[enemies[0].x][enemies[0].y] = &enemies[0];
				enemies[0].health = 1;
				break;
			}
		}
		while (true) {
			enemies[1].x = rand() % BOARD_SIZE;
			enemies[1].y = rand() % BOARD_SIZE;
			if (board.grid[enemies[1].x][enemies[1].y] == nullptr) {
				board.grid[enemies[1].x][enemies[1].y] = &enemies[1];
				enemies[0].health = 1;
				break;
			}
		}
		return true;
	}

	bool Attack(int direction) {
		int target_x, target_y;
		SetNewCoordinates(direction, &target_x, &target_y);
		if (board.grid[target_x][target_y] != nullptr && board.grid[target_x][target_y]->type == "ENEMY") {
			if ((*board.grid[target_x][target_y]).Damage(player.damage)) {
				board.grid[target_x][target_y] = nullptr;
			}
			return true;
		}
		return false;
	}

	void GameOver() {
		system("CLS");
		std::cout << "GAME OVER, PRESS ANY BUTTON TO CLOSE THE GAME\n";
		std::cin.get();
	}
};