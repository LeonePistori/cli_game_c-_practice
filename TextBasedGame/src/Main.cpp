#include<iostream>
#include<string>
#include<fstream>
#include<Controller.h>

#define DIRECTIONS
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define ACTIONS
#define MOVE 0
#define ATTACK 1
#define NEXT 2

void ParseInput(std::string input, int* action);

int main()
{
	Controller controller;
	std::string input;
	int action[2];
	bool result = true;

	controller.Init();
	std::cin.get();
	controller.board.Print(controller.player.health);
	while (true) {
		std::getline(std::cin, input);
		if (input == std::string("QUIT")) {
			break;
		}
		ParseInput(input, action);
		if (action[0] == MOVE) result = controller.Move(action[1]);
		else if (action[0] == ATTACK) result = controller.Attack(action[1]);
		else if (action[0] == NEXT) result = controller.SpawnEnemies();
		if (!result) {
			std::cout << "Illegal move, retry\n";
		}
		controller.EnemyMove();
		if (controller.player.health < 1) {
			controller.GameOver();
			break;
		}
		controller.board.Print(controller.player.health);
	}

}

void ParseInput(std::string input, int* action) {
	unsigned int curr_position = 0;
	unsigned int end_of_word_position = 0;
	unsigned int length = 0;
	int curr_word = 0;
	std::string parsed_input[2];
	while (true) {
		curr_position = end_of_word_position;
		end_of_word_position = input.find(' ', curr_position + 1);
		if (end_of_word_position == std::string::npos) length = std::string::npos;
		else length = end_of_word_position - curr_position;
		if (curr_position == std::string::npos) break;
		else {
			if(curr_position != 0) parsed_input[curr_word] = input.substr(curr_position + 1, length - 1);
			else parsed_input[curr_word] = input.substr(curr_position, length);
		}
		curr_word = curr_word + 1;
	}
	if (parsed_input[0] == "ATTACK") action[0] = ATTACK;
	else if (parsed_input[0] == "MOVE") action[0] = MOVE;
	else if (parsed_input[0] == "NEXT") action[0] = NEXT;
	if (parsed_input[1] == "UP") action[1] = UP;
	else if (parsed_input[1] == "RIGHT") action[1] = RIGHT;
	else if (parsed_input[1] == "DOWN") action[1] = DOWN;
	else if (parsed_input[1] == "LEFT") action[1] = LEFT;
}