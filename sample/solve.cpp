/**
 * solve.cpp
 * 
 * Test of solve.
 */

#include <iostream>
#include <list>

#include <getopt.h>
#include <stdlib.h>

#include <basiccube3.h>
#include <constants.h>
#include <solution.h>

void usage() {
    std::cerr << "Usage: solve [--scramble <scramble-sequence>]" << std::endl;
    exit(-1);
}

void version() {
    std::cerr << "Version: solve 0.1" << std::endl;
    exit(-1);
}

int main(int argc, char *argv[]) {
    // Options
    char *input_scramble = NULL;

    struct option longopts[] = {
        {"scramble", required_argument, NULL, 's'},
        {"version",  no_argument,       NULL, 'v'},
        {"help",     no_argument,       NULL, 'h'},
        {0, 0, 0, 0}
    };
    int opt, optidx;
    while ((opt = getopt_long(argc, argv, "s:vh", longopts, &optidx)) != -1) {
        switch (opt) {
            case 's':
                input_scramble = optarg;
                break;
            case 'v':
                version();
                break;
            case 'h':
            case ':':
            case '?':
            default:
                usage();
        }
    }

    std::string scramble;
    if (input_scramble != NULL) {
        scramble = input_scramble;
        std::cout << "Scramble: " << scramble << std::endl;
    } else {
        scramble = "U' L2 F2 D R2 F2 D' B2 L2 U2 R F L' D' F' L' D' F' L' D2 B'";
        std::cout << "Scramble: " << scramble << " (sample)" << std::endl;
    }

    Sarumawashi::BasicCube3 *cube = new Sarumawashi::BasicCube3();
    cube->init(scramble);
    Sarumawashi::Solution *s = new Sarumawashi::Solution(*cube);
    s->solve();
    std::cout << "Final solution: " << s->get_in_str() << std::endl;

    return 0;
}
