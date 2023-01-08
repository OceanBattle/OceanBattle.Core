#include <impl/Map.hpp>
#include <iostream>


Map::Map(int mapSize) {
    _rawMap = new int * [mapSize];
    for (int x = 0; x < mapSize; x++){
        _rawMap[x] = new int[mapSize];
    }

    for (int x = 0; x < mapSize; x++) {
        for (int y = 0; y < mapSize; y++) {
            _rawMap[x][y] = 0;
        }
    }

    _indices = new float [mapSize * mapSize * 2];

    // float xPos{0}, yPos{0};
    int xiPos{0}, yiPos{0};
    // float floatMapSize = mapSize - 1.f;

    for (int x = 0; x < mapSize * mapSize * 2; x += 2) {

        // _indices[x] = xPos;
        // _indices[x + 1] = yPos;

        // if (xPos > (floatMapSize - 1.f) * MAP_VERTICES_SPACING ) {
        //     xPos = 0;
        //     yPos += MAP_VERTICES_SPACING;
        //     continue;
        // }

        // xPos += MAP_VERTICES_SPACING;

        // VERSION 2
        // if ((floatMapSize * MAP_VERTICES_SPACING) - xPos < 0.0000001 ) {
        //     xPos = 0;
        //     yPos += MAP_VERTICES_SPACING;
        // }

        // _indices[x] = xPos;
        // // std::cout << xPos << std::endl;
        // _indices[x + 1] = yPos;

        // xPos += MAP_VERTICES_SPACING;
        // END OF VERSION 2
        // std::cout << floatMapSize * MAP_VERTICES_SPACING << std::endl;


        // VERSION 3

        if(xiPos == mapSize){
            xiPos = 0;
            yiPos++;
        }

        _indices[x] = xiPos;
        _indices[x + 1] = yiPos;

        xiPos++;


    }


    for (int x = 0; x < mapSize * mapSize * 2; x++){
        _indices[x] *= MAP_VERTICES_SPACING;
    }

    _size = mapSize;
    _createdLocaly = true;
}

float * Map::MapIndices() {
    return _indices;
}

Map::Map(int ** map){
    _rawMap = map;
}

Map::~Map() {

    if (_createdLocaly) 
    {
        for (int x = 0; x < _size; x++) {
            delete[] _rawMap[x];

        }

        delete[] _rawMap;

    }
    delete[] _indices;

}


int ** Map::RawMap(){
    return _rawMap;
}

int Map::Size() {
    return _size;
}


void Map::AddShip(int x, int y, int size, Rotation rotation) {

    // Add to rawmap
    for (int k = 0; k < size; k++) {
        switch (rotation) {
            case top:
                _rawMap[x][y-k] = size;
                break;
            case down:
                _rawMap[x][y+k] = size;
                break;
            case left:
                _rawMap[x-k][y] = size;
                break;
            case right:
                _rawMap[x+k][y] = size;
                break;
        }
        
    }

}

void Map::SetRawMap(int **raw){
    _rawMap = raw;
}
