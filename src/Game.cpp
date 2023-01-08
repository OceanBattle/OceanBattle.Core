#include "impl/LocalMap.hpp"
#include "impl/Map.hpp"
#include <impl/Game.hpp>

#define APPNAME "OceanBattle"

namespace Core 
{


    void Game::Open(int gameSize) {
        _windowProperties.width = 800;
        _windowProperties.height = 800;
        _windowProperties.name = APPNAME;

        _windowService.StartWindow(&_windowProperties);

        _localMap = new LocalMap(gameSize);
        _serverMap = new Map(gameSize);
        _windowService.SetLocalMap(_localMap->GetMap());
        _windowService.SetServerMap(_serverMap);
        _windowService.SetRotationPtr(_localMap->GetRotation());
        // Here lacs somethink   
    }

    void Game::Move(int orientation){
        if(orientation == 2) {
            _windowService.MoveCursor(top);
        }
        if(orientation == 1) {
            _windowService.MoveCursor(right);
        }
        if(orientation == 0) {
            _windowService.MoveCursor(down);
        }
        if(orientation == 3) {
            _windowService.MoveCursor(left);
        }

        // Everythink
    }

    void Game::Rotate() {
        _localMap->RotateShip();
    }

    void Game::SelectShip(int size){
        _localMap->SetSize(size);
        _windowService.SetLengthShip(size);
    }

    void Game::SwapMap() {
        _windowService.SwapRenderMap();
    }

    void Game::Render() {
        // _windowService.DrawMap();
        _windowService.Update();
    }


    bool Game::PlaceShip() {
        return _localMap->PlaceShip(_windowService.GetCursorPosition()[0], _windowService.GetCursorPosition()[1]);
    }

    void Game::GameEnd() {
        _windowService.Close();
        delete _localMap;
        delete _serverMap;
    }

    void Game::ReceiveShipPlaced(int **map) {
        _localMap->SetRawMap(map);
        _windowService.SetLocalMap(_localMap->GetMap());
    }

    void Game::GotHit(int **newMap) {
        ReceiveShipPlaced(newMap);
    }

    void Game::SendHit(int * x, int * y){
        *x = _windowService.GetCursorPosition()[0]; 
        *y = _windowService.GetCursorPosition()[1]; 
    }

    void Game::ReceiveEnemyMap(int **enemyMap) {
        _serverMap->SetRawMap(enemyMap);
        _windowService.SetServerMap(_serverMap);
    }


}