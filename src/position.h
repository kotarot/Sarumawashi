/**
 * position.h
 * 
 * A position of each corner/edge in a 3D orthogonal coordinate system.
 *   - Direction of x-axis is R-face -> L-face
 *   - Direction of y-axis is U-face -> D-face
 *   - Direction of z-axis is F-face -> B-face
 *
 * @author kotarot
 * @version 0.1 2014-10-16
 */

#ifndef __POSITION_H__
#define __POSITION_H__

#include "constants.h"

namespace Sarumawashi {

class Position {
public:
    // (x, y, z) are coordinates.
    int8_t  x;
    int8_t  y;
    int8_t  z;
    // r is a count of rotations.
    // [for corners]
    //   3n:   does not pivot.
    //   3n+1: pivots once clockwise, or pivots twice counter-clockwise.
    //   3n+2: pivots once counter-clockwise, or pivots twice clockwise.
    // [for edges]
    //   2n:   does not flip.
    //   2n+1: flips.
    uint8_t r;

    Position() : x(0), y(0), z(0), r(0) {};
    Position(int ax, int ay, int az) : x(ax), y(ay), z(az), r(0) {};
    Position(int ax, int ay, int az, int ar) : x(ax), y(ay), z(az), r(ar) {};
    ~Position() {};

    /** Rotations of a position. */
    /** Rotates around x-axis clockwise from the bottom view by (n*PI)/2 rad. */
    void rot_x(int n);
    /** Rotates around y-axis clockwise from the bottom view by (n*PI)/2 rad. */
    void rot_y(int n);
    /** Rotates around z-axis clockwise from the bottom view by (n*PI)/2 rad. */
    void rot_z(int n);
};

} // end of namespace

#endif
