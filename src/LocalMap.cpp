#include "impl/Map.hpp"
#include <impl/LocalMap.hpp>
#include <vector>


LocalMap::LocalMap(int mapSize) : _mapInstance(mapSize) {};

// LocalMap::LocalMap(){

// }

bool LocalMap::PlaceShip(int x, int y, int size){

    // checks if coorddinates are inside map
    if (x >= _mapInstance.Size() || y >= _mapInstance.Size()) return false;
    if (x < 0 || y < 0) return false;

    switch (_rotation) {
        case top:
            if (y - size + 1 < 0) return false;
            break;
        case down:
            if (y + size - 1 >= _mapInstance.Size()) return false;
            break;
        case left:
            if (x - size + 1 < 0) return false;
            break;
        case right:
            if (x + size - 1 >= _mapInstance.Size()) return false;
            break;
    }

    int ** rawmap = _mapInstance.RawMap();

    switch (_rotation) {
        case top:
            for (int k = 0; k < size; k++) {
                if (rawmap[x][y - k] != 0) return false;
            }
            break;
        case down:
            for (int k = 0; k < size; k++) {
                if (rawmap[x][y + k] != 0) return false;
            }
            break;
        case left:
            for (int k = 0; k < size; k++) {
                if (rawmap[x - k][y] != 0) return false;
            }
            break;
        case right:
            for (int k = 0; k < size; k++) {
                if (rawmap[x + k][y] != 0) return false;
            }
            break;
    }

    _mapInstance.AddShip(x, y, size, _rotation);
    return true;


}

void LocalMap::RotateShip() {
    switch (_rotation) {
        case top:
            _rotation = right;
            break;
        case right:
            _rotation = down;
            break;
        case down:
            _rotation = left;
            break;
        case left:
            _rotation = top;
            break;
    }
}

Map * LocalMap::GetMap() {
    return &_mapInstance;
}

Rotation * LocalMap::GetRotation() {
    return &_rotation;
}

void LocalMap::SetSize(int x) {
    _size = x;
}

bool LocalMap::PlaceShip(int x, int y) {
    PlaceShip(x, y, _size);
    return true;
}

void LocalMap::SetRawMap(int **map) {
    _mapInstance.SetRawMap(map);
}