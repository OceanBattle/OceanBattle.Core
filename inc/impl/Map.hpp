#ifndef __MAP__
#define __MAP__

#define MAP_VERTICES_SPACING 0.6f

enum Rotation {
    top,
    right,
    down,
    left
};


// Stores information about map
class Map {
    public:
        Map(int mapSize);
        ~Map();

        int Size();
        void AddShip(int x, int y, int size, Rotation rotation);
        int ** RawMap();
        float * MapIndices();

    private:
        int _size;
        int ** _rawMap;
        float * _indices;
};

#endif