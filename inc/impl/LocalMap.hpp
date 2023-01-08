#ifndef __LOCALMAP__
#define __LOCALMAP__

#include <impl/Map.hpp>


// Class related to game.
// It,s logic base.
class LocalMap {
    public:
        // Creates instance of ship game with map size.
        LocalMap(int mapSize);
        LocalMap();
        
        // Place ship on x,y.
        // Returns true if can place.
        bool PlaceShip(int x, int y, int size);

        bool PlaceShip(int x, int y);

        // Rotates ship to be placed
        void RotateShip();

        Rotation * GetRotation();

        // Gets current map data.
        Map * GetMap();

        void SetSize(int x);

        void SetRawMap(int ** map);


    private:
        int _size;
        Rotation _rotation = top;
        Map _mapInstance;
};

#endif