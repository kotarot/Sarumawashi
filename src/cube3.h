/**
 * cube3.h
 * 
 * Class of a cube puzzle (3x3x3), holds a cube state (position and facelets).
 * 
 * @author kotarot
 * @version 2014-10-20
 */

#ifndef __CUBE3_H__
#define __CUBE3_H__

#include "constants.h"
#include "position.h"
#include "basiccube3.h"

namespace Sarumawashi {

class Cube3 : public BasicCube3 {
public:
    Cube3() {};
    ~Cube3() {};

    /** Init the cube, make it to the solved state. */
    void init();
    /** Init the cube with a given sequence. */
    void init(const std::string sequence);
    /** Checks if the cube is solved or not. */
    //bool is_solved();
    /** Shows sub-cubes of corners and edges individually for debugging. */
    void print_cubes();
    /** Shows the development. */
    void print_development();

    /** Some overloaded turn operations. */
    /** @param face in face_t such as U, F, ...,
               rotation in rotation_t such as CW, HALF, ... */
    void turn(const face_t f, const rotation_t r);
    /** @param face in char such as 'U', 'F', ...,
               rotation in char such as ' ', '\0', '\'', '2'. */
    void turn(const char f, const char r);
    /** @param face and rotation in std::string such as "U", "U'", "U2", ... */
    void turn(const std::string note);

    /** Performs given sequence of moves on the cube. */
    void perform_sequence(const std::string sequence);

    /** Sets the cube to a well-known state given by name. */
    void wellknown(std::string name);

protected:
    /** State of the cube (corner-cubes and edge-cubes). */
    cornercube_t ccube[NUM_OF_CORNERS];
    edgecube_t   ecube[NUM_OF_EDGES];

    /** Sets sub-cubes from a new positions. */
    void positions_to_cubes();

    /** Developments of each face in a line. */
    std::string development_r();
    std::string development_l();
    std::string development_u();
    std::string development_d();
    std::string development_f();
    std::string development_b();

};

} // end of namespace

#endif
