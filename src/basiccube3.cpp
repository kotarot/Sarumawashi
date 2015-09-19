/**
 * basiccube3.cpp
 * 
 * Definitions of basiccube3.h
 * 
 * @author kotarot
 * @version 2014-10-20
 */

#include <cstdio>
#include "constants.h"
#include "basiccube3.h"
#include "utils.h"

namespace Sarumawashi {

/** Init the cube, make it to the solved state. */
void BasicCube3::init() {
    int c = 0, e = 0;
    for (int i = 0; i < 20; i++) {
        if (default_pos[i][0] == 0) { // corners
            cpos[c].z = default_pos[i][1];
            cpos[c].y = default_pos[i][2];
            cpos[c].x = default_pos[i][3];
            c++;
        } else { // edges
            epos[e].z = default_pos[i][1];
            epos[e].y = default_pos[i][2];
            epos[e].x = default_pos[i][3];
            e++;
        }
    }
}

/** Init the cube with a given sequence. */
void BasicCube3::init(const std::string sequence) {
    std::vector<std::string> moves;

    init();
    moves = split(sequence, ' ');
    for (std::vector<std::string>::iterator i = moves.begin();
         i != moves.end(); i++) {
        basic_turn(*i);
    }
}

/** Checks if the cube is solved or not. */
bool BasicCube3::is_solved() {
    int c = 0, e = 0;
    for (int i = 0; i < 20; i++) {
        if (default_pos[i][0] == 0) { // corners
            if (cpos[c].z != default_pos[i][1] ||
                cpos[c].y != default_pos[i][2] ||
                cpos[c].x != default_pos[i][3] ||
                cpos[c].r % 3 != 0) {
                return false;
            }
            c++;
        } else { // edges
            if (epos[e].z != default_pos[i][1] ||
                epos[e].y != default_pos[i][2] ||
                epos[e].x != default_pos[i][3] ||
                epos[e].r % 2 != 0) {
                return false;
            }
            e++;
        }
    }
    return true;
}

/** Checks if the cube is valid state, which means it is reachable from
    the solved state. */
bool BasicCube3::is_valid() {
    // TODO: implemented later.
    return true;
}

/** Shows positions of corners and edges individually for debugging. */
void BasicCube3::print_positions() {
    printf("pos|corners\n");
    for (int i = 0; i < NUM_OF_CORNERS; i++) {
        printf("  %2d %s: (%2d, %2d, %2d), %d\n", i, dbg_corners[i].c_str(),
               cpos[i].x, cpos[i].y, cpos[i].z, cpos[i].r);
    }
    printf("pos|edges\n");
    for (int i = 0; i < NUM_OF_EDGES; i++) {
        printf("  %2d %s: (%2d, %2d, %2d), %d\n", i, dbg_edges[i].c_str(),
               epos[i].x, epos[i].y, epos[i].z, epos[i].r);
    }
}

/** Serializes the cube state to string. */
std::string BasicCube3::serialize() {
    // TODO: implemented later.
    return "serialized string.";
}

/** Sets the cube to the serialized state. */
void BasicCube3::unserialize(const std::string serialized) {
    // TODO: implemented later.
}

corner_t BasicCube3::corner(const int8_t x, const int8_t y, const int8_t z) {
    for (int i = 0; i < NUM_OF_CORNERS; i++) {
        if (cpos[i].x == x && cpos[i].y == y && cpos[i].z == z) {
            return (corner_t)i;
        }
    }
    return NUM_OF_CORNERS;
}

edge_t BasicCube3::edge(const int8_t x, const int8_t y, const int8_t z) {
    for (int i = 0; i < NUM_OF_EDGES; i++) {
        if (epos[i].x == x && epos[i].y == y && epos[i].z == z) {
            return (edge_t)i;
        }
    }
    return NUM_OF_EDGES;
}

/** Some overloaded turn operations. */
void BasicCube3::basic_turn(const face_t f, const rotation_t r) {
    int quarters = (int)r;
    int direction = 1;
    if (f == L || f == D || f == B) {
        direction = -1;
    }

    // corners
    std::vector<corner_t> cv = corners_on(f);
    for (int i = 0; i < 4; i++) {
        int idx = cv[i];
        if (f == R || f == L) {
            cpos[idx].rot_x(direction * quarters);
        } else if (f == U || f == D) {
            cpos[idx].rot_y(direction * quarters);
        } else if (f == F || f == B) {
            cpos[idx].rot_z(direction * quarters);
        }
        for (int q = 0; q < quarters; q++) {
            cpos[idx].r += cparity[f][(i + q) % 4];
        }
    }
    // edges
    std::vector<edge_t> ev = edges_on(f);
    for (int i = 0; i < 4; i++) {
        int idx = ev[i];
        if (f == R || f == L) {
            epos[idx].rot_x(direction * quarters);
        } else if (f == U || f == D) {
            epos[idx].rot_y(direction * quarters);
        } else if (f == F || f == B) {
            epos[idx].rot_z(direction * quarters);
        }
        for (int q = 0; q < quarters; q++) {
            epos[idx].r += eparity[f][(i + q) % 4];
        }
    }
}

void BasicCube3::basic_turn(const char fc, const char rc) {
    face_t f;
    rotation_t r;
    if (fc == 'R' || fc == 'r') {
        f = R;
    } else if (fc == 'L' || fc == 'l') {
        f = L;
    } else if (fc == 'U' || fc == 'u') {
        f = U;
    } else if (fc == 'D' || fc == 'd') {
        f = D;
    } else if (fc == 'F' || fc == 'f') {
        f = F;
    } else if (fc == 'B' || fc == 'b') {
        f = B;
    } else {
        return;
    }
    if (rc == '\0' || rc == ' ') {
        r = CW;
    } else if (rc == '2') {
        r = HALF;
    } else if (rc == '\'') {
        r = CCW;
    } else {
        return;
    }
    basic_turn(f, r);
}

void BasicCube3::basic_turn(const std::string symbol) {
    char fc;
    char rc = '\0';
    if (symbol.length() < 1) {
        return;
    }
    fc = symbol.at(0);
    if (symbol.length() != 1) {
        rc = symbol.at(1);
    }
    basic_turn(fc, rc);
}

/** Returns the vector of corners and edges on each face. */
std::vector<corner_t> BasicCube3::corners_on(face_t f) {
    std::vector<corner_t> ret;
    for (int i = 0; i < 4; i++) {
        ret.push_back(corner(cornercubes[f][i][0], cornercubes[f][i][1],
                             cornercubes[f][i][2]));
    }
    return ret;
}

std::vector<edge_t> BasicCube3::edges_on(face_t f) {
    std::vector<edge_t> ret;
    for (int i = 0; i < 4; i++) {
        ret.push_back(edge(edgecubes[f][i][0], edgecubes[f][i][1],
                           edgecubes[f][i][2]));
    }
    return ret;
}

} // end of namespace
