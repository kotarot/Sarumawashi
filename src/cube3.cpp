/**
 * cube3.cpp
 * 
 * Definitions of cube3.h
 * 
 * @author kotarot
 * @version 2014-10-20
 */

#include <cstdio>
#include <sstream>
#include <string>
#include "constants.h"
#include "cube3.h"
#include "basiccube3.h"

namespace Sarumawashi {

/** Init the cube, make it to the solved state. */
void Cube3::init() {
    // positions
    int c = 0, e = 0;
    for (int nz = -1; nz <= 1; nz++) {
        for (int ny = -1; ny <= 1; ny++) {
            for (int nx = -1; nx <= 1; nx++) {
                if ((nx == 0 && ny == 0) || (ny == 0 && nz == 0) ||
                    (nz == 0 && nx == 0)) { // center cubes, including core
                    continue;
                } else if (nx == 0 || ny == 0 || nz == 0) { // edges
                    epos[e].x = nx;
                    epos[e].y = ny;
                    epos[e].z = nz;
                    epos[e].r = 0;
                    e++;
                } else { // corners
                    cpos[c].x = nx;
                    cpos[c].y = ny;
                    cpos[c].z = nz;
                    cpos[c].r = 0;
                    c++;
                }
            }
        }
    }
    // cubes
    for (int i = 0; i < NUM_OF_CORNERS; i++) {
        ccube[i].c = (corner_t)i;
        ccube[i].p = (uint8_t)0;
    }
    for (int i = 0; i < NUM_OF_EDGES; i++) {
        ecube[i].c = (edge_t)i;
        ecube[i].p = (uint8_t)0;
    }
}

/** Init the cube with a given sequence. */
void Cube3::init(const std::string sequence) {
    init();
    perform_sequence(sequence);
}

/** Checks if the cube is solved or not. */
#if 0
bool Cube3::is_solved() {
    for (int i = 0; i < NUM_OF_CORNERS; i++) {
        if (ccube[i].c != (corner_t)i || ccube[i].p % 3 != 0) {
            return false;
        }
    }
    for (int i = 0; i < NUM_OF_EDGES; i++) {
        if (ecube[i].c != (edge_t)i || ecube[i].p % 2 != 0) {
            return false;
        }
    }
    return true;
}
#endif

/** Shows sub-cubes of corners and edges individually for debugging. */
void Cube3::print_cubes() {
    printf("cube|corners\n");
    for (int i = 0; i < NUM_OF_CORNERS; i++) {
        printf("  %2d %s: %s %d\n", i, dbg_corners[i].c_str(),
               dbg_corners[ccube[i].c].c_str(), ccube[i].p);
    }
    printf("cube|edges\n");
    for (int i = 0; i < NUM_OF_EDGES; i++) {
        printf("  %2d %s: %s %d\n", i, dbg_edges[i].c_str(),
               dbg_edges[ecube[i].c].c_str(), ecube[i].p);
    }
}

/** Shows the development. */
void Cube3::print_development() {
    // Gets devleopments string of each face.
    std::string r = development_r();
    std::string l = development_l();
    std::string u = development_u();
    std::string d = development_d();
    std::string f = development_f();
    std::string b = development_b();

    printf("-----------------\n");
    // U-face
    printf("     %s         \n     %s         \n     %s         \n",
           u.substr(0, 3).c_str(), u.substr(3, 3).c_str(),
           u.substr(6, 3).c_str());
    // L-F-R-B-face
    printf(" %s %s %s %s \n %s %s %s %s \n %s %s %s %s \n",
           l.substr(0, 3).c_str(), f.substr(0, 3).c_str(),
           r.substr(0, 3).c_str(), b.substr(0, 3).c_str(),
           l.substr(3, 3).c_str(), f.substr(3, 3).c_str(),
           r.substr(3, 3).c_str(), b.substr(3, 3).c_str(),
           l.substr(6, 3).c_str(), f.substr(6, 3).c_str(),
           r.substr(6, 3).c_str(), b.substr(6, 3).c_str());
    // D-face
    printf("     %s         \n     %s         \n     %s         \n",
           d.substr(0, 3).c_str(), d.substr(3, 3).c_str(),
           d.substr(6, 3).c_str());
    printf("-----------------\n");
}

/** Some overloaded turn operations. */
void Cube3::turn(const face_t f, const rotation_t r) {
    basic_turn(f, r);
    positions_to_cubes();
}

void Cube3::turn(const char fc, const char rc) {
    basic_turn(fc, rc);
    positions_to_cubes();
}

void Cube3::turn(const std::string symbol) {
    basic_turn(symbol);
    positions_to_cubes();
}

/** Performs given sequence of moves on the cube. */
void Cube3::perform_sequence(const std::string sequence) {
    std::vector<std::string> moves;

    moves = split(sequence, ' ');
    for (std::vector<std::string>::iterator i = moves.begin();
	 i != moves.end(); i++) {
	turn(*i);
    }
}

/** Sets the cube to a well-known state given by name. */
void Cube3::wellknown(std::string name) {
    if (name == "superflip") {
        init("U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2");
    } else if (name == "checkers") {
        init("U2 D2 R2 L2 F2 B2");
    }
}

/** Sets sub-cubes from a new positions. */
void Cube3::positions_to_cubes() {
    int c = 0, e = 0;
    for (int z = -1; z <= 1; z++) {
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                if ((x == 0 && y == 0) || (y == 0 && z == 0) ||
                    (z == 0 && x == 0)) { // center cubes, including core
                    continue;
                } else if (x == 0 || y == 0 || z == 0) { // edges
                    edge_t idx = edge(x, y, z);
                    ecube[e].c = idx;
                    ecube[e].p = epos[idx].r;
                    e++;
                } else { // corners
                    corner_t idx = corner(x, y, z);
                    ccube[c].c = idx;
                    ccube[c].p = cpos[idx].r;
                    c++;
                }
            }
        }
    }
}

/** Developments of each face in a line. */
std::string Cube3::development_r() {
    std::stringstream ret;
    int c = 0;
    for (int y = -1; y <= 1; y++) {
        for (int z = -1; z <= 1; z++) {
            if (y == 0 && z == 0) { // center
                ret << "R";
            } else if (y == 0 || z == 0) { // edge
                int idx = edge(-1, y, z);
                ret << dbg_edges[idx].at((epos[idx].r + 1) % 2);
            } else { // corner
                int idx = corner(-1, y, z);
                ret << dbg_corners[idx].at((cpos[idx].r + cdev[c]) % 3);
                c++;
            }
        }
    }
    return ret.str();
}

std::string Cube3::development_l() {
    std::stringstream ret;
    int c = 0;
    for (int y = -1; y <= 1; y++) {
        for (int z = 1; z >= -1; z--) {
            if (y == 0 && z == 0) { // center
                ret << "L";
            } else if (y == 0 || z == 0) { // edge
                int idx = edge(1, y, z);
                ret << dbg_edges[idx].at((epos[idx].r + 1) % 2);
            } else { // corner
                int idx = corner(1, y, z);
                ret << dbg_corners[idx].at((cpos[idx].r + cdev[c]) % 3);
                c++;
            }
        }
    }
    return ret.str();
}

std::string Cube3::development_u() {
    std::stringstream ret;
    for (int z = 1; z >= -1; z--) {
        for (int x = 1; x >= -1; x--) {
            if (z == 0 && x == 0) { // center
                ret << "U";
            } else if (z == 0 || x == 0) { // edge
                int idx = edge(x, -1, z);
                ret << dbg_edges[idx].at(epos[idx].r % 2);
            } else { // corner
                int idx = corner(x, -1, z);
                ret << dbg_corners[idx].at(cpos[idx].r % 3);
            }
        }
    }
    return ret.str();
}

std::string Cube3::development_d() {
    std::stringstream ret;
    for (int z = -1; z <= 1; z++) {
        for (int x = 1; x >= -1; x--) {
            if (z == 0 && x == 0) { // center
                ret << "D";
            } else if (z == 0 || x == 0) { // edge
                int idx = edge(x, 1, z);
                ret << dbg_edges[idx].at(epos[idx].r % 2);
            } else { // corner
                int idx = corner(x, 1, z);
                ret << dbg_corners[idx].at(cpos[idx].r % 3);
            }
        }
    }
    return ret.str();
}

std::string Cube3::development_f() {
    std::stringstream ret;
    int c = 0, e = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = 1; x >= -1; x--) {
            if (y == 0 && x == 0) { // center
                ret << "F";
            } else if (y == 0 || x == 0) { // edge
                int idx = edge(x, y, -1);
                ret << dbg_edges[idx].at((epos[idx].r + edev[e]) % 2);
                e++;
            } else { // corner
                int idx = corner(x, y, -1);
                ret << dbg_corners[idx].at((cpos[idx].r + cdev[c]) % 3);
                c++;
            }
        }
    }
    return ret.str();
}

std::string Cube3::development_b() {
    std::stringstream ret;
    int c = 0, e = 0;
    for (int y = -1; y <= 1; y++) {
        for (int x = -1; x <= 1; x++) {
            if (y == 0 && x == 0) { // center
                ret << "B";
            } else if (y == 0 || x == 0) { // edge
                int idx = edge(x, y, 1);
                ret << dbg_edges[idx].at((epos[idx].r + edev[e]) % 2);
                e++;
            } else { // corner
                int idx = corner(x, y, 1);
                ret << dbg_corners[idx].at((cpos[idx].r + cdev[c]) % 3);
                c++;
            }
        }
    }
    return ret.str();
}

/** Splits a string. Refference:
    http://qiita.com/iseki-masaya@github/items/70b4ee6e0877d12dafa8 */
std::vector<std::string> split(const std::string &s, const char delim) {
    std::vector<std::string> elems;
    std::string item;
    for (int i = 0; i < (int)s.length(); i++) {
        char ch = s.at(i);
        if (ch == delim) {
            if (!item.empty()) {
                elems.push_back(item);
            }
            item.clear();
        } else {
            item += ch;
        }
    }
    if (!item.empty()) {
        elems.push_back(item);
    }
    return elems;
}

} // end of namespace
