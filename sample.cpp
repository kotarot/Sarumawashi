/**
 * sample.cpp
 * 
 * How to use Sarumawashi.
 */

#include <iostream>

#include <cube3.h>
#include <wellknowncube3.h>
#include <constants.h>

int main() {
    //// Example 1 ////
    Sarumawashi::Cube3 *cube1 = new Sarumawashi::Cube3();

    // Sets to the solved state.
    cube1->init();

    // Checks if the cube is solved.
    std::cout << cube1->is_solved() << std::endl;

    // One turning move.
    cube1->turn(Sarumawashi::R, Sarumawashi::CW);
    cube1->turn('U', '2');
    cube1->turn("F'");
    std::cout << cube1->is_solved() << std::endl;

    // Shows the states.
    cube1->print_positions();
    cube1->print_cubes();
    cube1->print_development();

    //// Example 2 ////
    Sarumawashi::Cube3 *cube2 = new Sarumawashi::Cube3();

    // Sets the cube with a while-space separated sequence string.
    cube2->init("R U' F2 L D' B2");

    // Shows the states.
    cube2->print_positions();
    cube2->print_cubes();
    cube2->print_development();

    //// Example 3 ////
    Sarumawashi::WellKnownCube3 *cube3 = new Sarumawashi::WellKnownCube3();

    // Init to the superflip.
    cube3->wellknown("superflip");

    // Shows the states.
    cube3->print_positions();
    cube3->print_cubes();
    cube3->print_development();

    delete cube1;
    delete cube2;
    delete cube3;

    return 0;
}
