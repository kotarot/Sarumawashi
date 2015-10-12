/**
 * size.cpp
 * 
 * This program just examines the size of class(objects).
 */

#include <iostream>

#include <constants.h>
#include <position.h>
#include <basiccube3.h>
#include <cube3.h>

int main() {
    std::cout << "The size of Sarumawashi::Position = "
         << sizeof(Sarumawashi::Position) << " byte" << std::endl;
    std::cout << "The size of Sarumawashi::Cube3 = "
         << sizeof(Sarumawashi::Cube3) << " byte" << std::endl;
    std::cout << "The size of Sarumawashi::BasicCube3 = "
         << sizeof(Sarumawashi::BasicCube3) << " byte" << std::endl;

    return 0;
}
