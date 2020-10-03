#pragma once

#include<Entity.h>
#include<stdlib.h>

#define BOARD_SIZE 10

class Board {
public:
	Entity* grid[BOARD_SIZE][BOARD_SIZE];

	Board() {
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				grid[i][j] = nullptr;
			}
		}
	}

	void Print(int health) {
		system("CLS");
		std::cout << "PLAYER HEALTH: " << health << "\n";
		for (int j = 0; j < 2*BOARD_SIZE + 1; j++) {
			for (int i = 0; i < 2*BOARD_SIZE + 1; i++) {
				if (j % 2 == 0) std::cout << '-';
				else {
					if (i % 2 == 0) std::cout << '|';
					else {
						if (grid[i/2][j/2] == nullptr) std::cout << ' ';
						else if (grid[i/2][j/2]->type == "PLAYER") std::cout << 'O';
						else if (grid[i/2][j/2]->type == "ENEMY") std::cout << '@';
					}
				}
			}
			std::cout << '\n';
		}
	}

	void PrintMenu() {
		system("CLS");
		std::cout << "Write ACTION DIRECTION to perform an action\n\n";
		std::cout << "ACTIONS:\n";
		std::cout << "MOVE\n";
		std::cout << "ATTACK\n";
		std::cout << "\n";
		std::cout << "DIRECTIONS:\n";
		std::cout << "UP\n";
		std::cout << "RIGHT\n";
		std::cout << "DOWN\n";
		std::cout << "LEFT\n";
		std::cout << "\n";
		std::cout << "PLAYER = O\n";
		std::cout << "ENEMY = @\n";
		std::cout << "\n";
		std::cout << "PRESS ANY BUTTON TO START THE GAME\n";
		std::cout << "WRITE NEXT AFTER HAVING DEFEAT BOTH ENEMIES TO SPAWN NEW ONES\n";
		std::cout << "DURING THE GAME WRITE 'QUIT' TO CLOSE THE GAME\n";
	}
};