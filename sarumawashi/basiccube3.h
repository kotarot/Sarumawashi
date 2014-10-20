/**
 * basiccube3.h
 * 
 * Basic class of a cube puzzle (3x3x3), holds a cube state (position of each 
 * sub-cubes), and defines some turn operations.
 * 
 * @author kotarot
 * @version 2014-10-20
 */

#ifndef __BASICCUBE3_H__
#define __BASICCUBE3_H__

#include <string>
#include <vector>
#include "constants.h"
#include "position.h"
#include "utils.h"

namespace Sarumawashi {

class BasicCube3 {
public:
    BasicCube3() {};
    ~BasicCube3() {};

    /** Init the cube, make it to the solved state. */
    void init();
    /** Init the cube with a given sequence. */
    void init(const std::string sequence);
    /** Checks if the cube is solved or not. */
    bool is_solved();
    /** Checks if the cube is valid state, which means it is reachable from
        the solved state. */
    bool is_valid();
    /** Shows positions of corners and edges individually for debugging. */
    void print_positions();
    /** Serializes the cube state to string. */
    std::string serialize();
    /** Sets the cube to the serialized state. */
    void unserialize(const std::string serialized);

    corner_t corner(const int8_t x, const int8_t y, const int8_t z);
    edge_t edge(const int8_t x, const int8_t y, const int8_t z);

    /** Some overloaded turn operations. */
    /** @param face in face_t such as U, F, ...,
               rotation in rotation_t such as CW, HALF, ... */
    void basic_turn(const face_t f, const rotation_t r);
    /** @param face in char such as 'U', 'F', ...,
               rotation in char such as ' ', '\0', '\'', '2'. */
    void basic_turn(const char f, const char r);
    /** @param face and rotation in std::string such as "U", "U'", "U2", ... */
    void basic_turn(const std::string note);

protected:
    /** State of the cube (positions of each corner and edge). */
    Position cpos[NUM_OF_CORNERS];
    Position epos[NUM_OF_EDGES];

    /** Returns vector of corners and edges on each face. */
    std::vector<corner_t> corners_on(face_t f);
    std::vector<edge_t>   edges_on(face_t f);

};

} // end of namespace

#endif
