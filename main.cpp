#include "impl/Map.hpp"
#include <cstdio>
#include <impl/WindowService.hpp>
#include <impl/LocalMap.hpp>
#include <iostream>
#include <impl/Game.hpp>



int main(){

    bool running = true;
    char move;

    Core::Game game;    
    game.Open(10);
    game.SelectShip(2);

    while(running) {
        game.Render();
        // game.Render();
        std::cin >> move;

        if (move == 'a') {
            game.Move(3);
        }
        if (move == 's') {
            game.Move(2);
        }
        if (move == 'd') {
            game.Move(1);
        }
        if (move == 'w') {
            game.Move(0);
        }
        if (move == 'q') {
            running = false;
        }
        if (move == 'p') {
            game.SwapMap();
        }
        if (move == 't') {
            game.PlaceShip();
        }
        if (move == 'r') {
            game.Rotate();
        }
        if (move == '+') {
            game.SelectShip(3);
        }
        if (move == '-') {
            game.SelectShip(1);
        }

    }

    game.GameEnd();

        
}