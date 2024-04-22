#include "pch.h"
#include "GameManager.h"

GameManager::GameManager(){}

GameManager::~GameManager()
{
	delete this->board;
	delete this->playerX;
	delete this->playerO;
}

bool GameManager::Init()
{
	this->board = new Board(13);
	std::string playerName;
	this->playerX = new Player();
	this->playerO = new Player();

	std::cout << "Enter the name of the player (playing for X): ";
	std::getline(std::cin, playerName);
	playerX->SetupPlayer(playerName, IntersectionType_X);
	std::cout << "Enter the name of the player (playing for O): ";
	std::getline(std::cin, playerName);
	playerO->SetupPlayer(playerName, IntersectionType_O);
	std::cout << std::endl;

	playerX->SetBoard(this->board);
	playerO->SetBoard(this->board);
	currentPlayer = playerX;

	return true;
}

void GameManager::ShowBoard()
{
	this->board->Show();
}

void GameManager::MakeMove()
{
	ShowBoard();
	
	currentPlayer->StartTimerAsync();

	while (!currentPlayer->MakeMove())
	{
		std::cout << "(!) ~~~ Bad move, try again" << std::endl;
		ShowBoard();
	}
	currentPlayer->PauseTimer();
	
	if (this->board->CheckEndCondition())
	{
		if (this->board->isVictory())
			std::cout << "(!) ~~~ The player " << currentPlayer->GetName() << " won!" << std::endl;
		else
			std::cout << "(!) ~~~ Drawn game!" << std::endl;
		this->bGameFinished = true;
		ShowBoard();
		return;
	}
	currentPlayer = (currentPlayer == playerX) ? playerO : playerX;
}

bool GameManager::isGameFinished() { return bGameFinished; }