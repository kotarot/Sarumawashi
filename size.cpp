/**
 * size.cpp
 * 
 * This program just examines the size of class(objects).
 */

#include <iostream>

#include <cube3.h>
#include <constants.h>

int main() {
    std::cout << "The size of Sarumawashi::Cube3 = "
         << sizeof(Sarumawashi::Cube3) << " byte" << std::endl;

    return 0;
}
