#ifndef SHIP_H
#define SHIP_H

#include <string>

class Ship {
private:
    std::string name;
    int size;

public:
    Ship(std::string shipName, int shipSize);
    ~Ship();

    std::string getName() const;
    int getSize() const;
};

#endif 
