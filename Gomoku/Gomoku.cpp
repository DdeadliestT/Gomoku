// Gomoku.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "pch.h"
#include <iostream>
#include "GameManager.h"

int main()
{
    GameManager manager;
    if (!manager.Init())
    {
        std::cout << "(!) ~~~ Something error, exit...";
        _getch();
        return 0;
    }

    while (!manager.isGameFinished()) { manager.MakeMove(); }
    _getch();
}