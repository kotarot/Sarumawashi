/**
 * cube3.h
 * 
 * Basic class of a cube puzzle (3x3x3), holds a cube state, and defines some
 * turn operations.
 * 
 * @author kotarot
 * @version 0.1 2014-10-16
 */

#ifndef __CUBE3_H__
#define __CUBE3_H__

#include <string>
#include <vector>
#include "constants.h"
#include "position.h"

namespace Sarumawashi {

class Cube3 {
public:
    Cube3() {};
    ~Cube3() {};

    /** Init the cube, make it to the solved state. */
    void init();
    /** Init the cube with a given sequence. */
    void init(const std::string sequence);
    /** Checks if the cube is solved or not. */
    bool is_solved();
    /** If it equals the state of the cube. */
    //bool equals(const Cube3 &trgt);
    /** Checks if the cube is valid state, which means it is reachable from
        the solved state. */
    bool is_valid();
    /** Shows positions of corners and edges individually for debugging. */
    void print_positions();
    /** Shows sub-cubes of corners and edges individually for debugging. */
    void print_cubes();
    /** Shows the development. */
    void print_development();
    /** Serializes the cube state to string. */
    std::string serialize();
    /** Sets the cube to the serialized state. */
    void unserialize(const std::string serialized);

    corner_t corner(const int8_t x, const int8_t y, const int8_t z);
    edge_t edge(const int8_t x, const int8_t y, const int8_t z);

    /** Some overloaded turn operations. */
    /** @param face in face_t such as U, F, ...,
               rotation in rotation_t such as CW, HALF, ... */
    void turn(const face_t f, const rotation_t r);
    /** @param face in char such as 'U', 'F', ...,
               rotation in char such as ' ', '\0', '\'', '2'. */
    void turn(const char f, const char r);
    /** @param face and rotation in std::string such as "U", "U'", "U2", ... */
    void turn(const std::string note);

    /** Sets the cube to a well-known state given by name. */
    void wellknown(std::string name);

protected:
    /** State of the cube (positions of each corner and edge). */
    Position cpos[NUM_OF_CORNERS];
    Position epos[NUM_OF_EDGES];
    /** State of the cube (corner-cubes and edge-cubes). */
    cornercube_t ccube[NUM_OF_CORNERS];
    edgecube_t   ecube[NUM_OF_EDGES];

    /** Sets sub-cubes from a new positions. */
    void positions_to_cubes();

    /** Returns vector of corners and edges on each face. */
    std::vector<corner_t> corners_on(face_t f);
    std::vector<edge_t>   edges_on(face_t f);

    /** Developments of each face in a line. */
    std::string development_r();
    std::string development_l();
    std::string development_u();
    std::string development_d();
    std::string development_f();
    std::string development_b();

};

/** Splits a string. Refference:
    http://qiita.com/iseki-masaya@github/items/70b4ee6e0877d12dafa8 */
std::vector<std::string> split(const std::string &s, const char delim);

} // end of namespace

#endif
