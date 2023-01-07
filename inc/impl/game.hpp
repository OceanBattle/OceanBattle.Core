#ifndef __GAME__
#define __GAME__

#include <vector>



enum ShipsType {
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE
};


struct ShipsStruct {
    ShipsType type;
    int position[2];
    int direction;
};


class Game {
    public:
    
        void GetShips(std::vector<ShipsType> ships);
        void GetMapSize(int size);

        void SetUp();
        std::vector<ShipsType> SentMap();


    private:
        std::vector<ShipsType> _shipsToPlace;

};



#endif