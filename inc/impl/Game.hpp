#ifndef __GAME__
#define __GAME__

#include <impl/LocalMap.hpp>
#include <impl/WindowService.hpp>
#include <impl/Map.hpp>

namespace Core 
{
    class Game 
    {
        public:
            // Opens window. ??
            void Open(int gameSize); // Mostly done i guess

            // Moves cursor.
            void Move(int orientation); // Done
            // Changes rotation.
            void Rotate(); // Done
            // Selects shipSize.
            void SelectShip(int size); // Done
            // got hit.
            void GotHit(int ** newMap); // Just gets new map to render


            // ??? Is it needed?
            void DeploymentStart();
            // Send place ship.


            bool PlaceShip(); // Done
            // Receives ??
            /* ??? */void ReceiveShipPlaced(int ** map); // Done i guess

            // // ??
            // void GameStart();


            // Receives hit.
            void ReceiveEnemyMap(int ** enemyMap); // Handle from CLi here done
            // Sents hit
            void SendHit(int * x, int * y); // Handle from CLI Here done
            // Swap render
            void SwapMap(); // Done
            // Renders frame
            void Render(); // Done


            // Close verythink
            void GameEnd(); // ? somethink missing probobly
            


        private:
            LocalMap * _localMap;
            Map * _serverMap;
            WindowService _windowService;
            WSUtils::WindowProperties _windowProperties;
            

    };
}


#endif