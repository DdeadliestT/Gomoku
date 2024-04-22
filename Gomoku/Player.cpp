#include "pch.h"
#include "Player.h"

Player::~Player(){}

void Player::StartTimerAsync() {
	isTimerPaused = false;
	std::thread timerThread([this]() {
		while (!isTimerPaused) {
			remainingTime = std::max(std::chrono::seconds(0), remainingTime - std::chrono::seconds(1));
			std::this_thread::sleep_for(std::chrono::seconds(1));

			if (remainingTime <= std::chrono::seconds(0)) {
				std::cout << "\n(!) ~~~ " << GetName() << " don`t have time to move (0s / 900s)";
				std::cout << "\n(!) ~~~ " << GetName() << " lost!\n";
				exit(0);
			}
		}
		});

	timerThread.detach(); // Отсоединение потока от объекта Player
}

void Player::SetupPlayer(std::string name, IntersectionType intersectionType)
{
	this->name = name;
	this->intersectionType = intersectionType;
}

bool Player::MakeMove()
{
	std::cout << "\nPlayer " << name << ", your move..." << std::endl;

	char str[256], * p = str;
	unsigned int row, col;

	std::cout << "Enter row: ";
	std::cin >> str;
	if (!CheckInput(p))
		return false;
	row = atoi(str);

	std::cout << "Enter column: ";
	std::cin >> str;
	if (!CheckInput(p))
		return false;
	col = atoi(str);

	if (this->board->CheckLegal(col, row))
	{
		this->board->SetIntersection(col, row, this->intersectionType);
		return true;
	}

	return false;
}

std::string Player::GetName()
{
	return this->name;
}

bool Player::CheckInput(char *p_str)
{
	while (*p_str)
		if (!isdigit(*p_str++))
			return false;
	return true;
}