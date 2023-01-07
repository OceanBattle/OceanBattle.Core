#ifndef __LOCALMAP__
#define __LOCALMAP__

#include <impl/Map.hpp>


// Class related to game.
// It,s logic base.
class LocalMap {
    public:
        // Creates instance of ship game with map size.
        LocalMap(int mapSize);
        
        // Place ship on x,y.
        // Returns true if can place.
        bool PlaceShip(int x, int y, int size);

        // Rotates ship to be placed
        void RotateShip();

        Rotation GetRotation();

        // Gets current map data.
        Map * GetMap();


    private:

        Rotation _rotation = top;
        Map _mapInstance;
};

#endif