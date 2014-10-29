/**
 * solve.cpp
 * 
 * Test of solve.
 */

#include <iostream>
#include <list>

#include <basiccube3.h>
#include <constants.h>
#include <solution.h>

int main() {
    Sarumawashi::BasicCube3 *cube = new Sarumawashi::BasicCube3();
    //std::string scramble = "U' L2 F2 D R2 F2 D' B2 L2 U2 R F L' D' F' L' D' F' L' D2 B'";
    std::string scramble = "R U L D";
    std::cout << "Scramble: " << scramble << std::endl;
    cube->init(scramble);
    Sarumawashi::Solution *s = new Sarumawashi::Solution(*cube);
    s->solve();
    std::cout << "Final solution: " << s->get_in_str() << std::endl;

    return 0;
}
