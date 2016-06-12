/**
 * check_solved.cpp
 * 
 * Checks if the cube is solved.
 */

#include <iostream>

#include <cube3.h>
#include <constants.h>

int main(int argc, char *argv[]) {
    Sarumawashi::Cube3 *cube = new Sarumawashi::Cube3();

    if (argc != 2) {
        return 1;
    } else {
        cube->init(argv[1]);
        if (cube->is_solved()) {
            std::cout << "1" << std::endl;
        } else {
            std::cout << "0" << std::endl;
        }
    }

    return 0;
}
