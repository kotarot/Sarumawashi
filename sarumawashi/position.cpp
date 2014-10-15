/**
 * position.cpp
 * 
 * Definitions of position.h
 * 
 * @author kotarot
 * @version 0.1 2014-10-16
 */

#include "constants.h"
#include "position.h"

namespace Sarumawashi {

/** Rotations of a position. */
/** Rotates around x-axis clockwise from the bottom view by (n*PI)/2 rad. */
void Position::rot_x(int n) {
    // Do nothing, if n is not meaningful value.
    if (n == 0 || n <= -4 || 4 <= n) {
        return;
    }
    if (n < 0) {
        // -1 -> 3, -2 -> 2, -3 -> 1
        // I do not use remainder of a negative, because it is not friendly
        // to understand.
        n = 4 + n;
    }
    // The coordinate of x will not change.
    // Rotate with a rotation matrix.
    // In the case of quarter turn clockwise (t = -PI/2),
    //   R = |cos(t) -sin(t)| = | 0 1|
    //       |sin(t)  cos(t)|   |-1 0|
    // applies to the coordinates,
    //   |y'| = R|y| = | 0 1||y| = | z|
    //   |z'|    |z|   |-1 0||z|   |-y|
    for (int i = 0; i < n; i++) {
        int8_t cy = y;
        y = z;
        z = -cy;
    }
}

/** Rotates around y-axis clockwise from the bottom view by (n*PI)/2 rad. */
void Position::rot_y(int n) {
    if (n == 0 || n <= -4 || 4 <= n) {
        return;
    }
    if (n < 0) {
        n = 4 + n;
    }
    for (int i = 0; i < n; i++) {
        int8_t cz = z;
        z = x;
        x = -cz;
    }
}

/** Rotates around z-axis clockwise from the bottom view by (n*PI)/2 rad. */
void Position::rot_z(int n) {
    if (n == 0 || n <= -4 || 4 <= n) {
        return;
    }
    if (n < 0) {
        n = 4 + n;
    }
    for (int i = 0; i < n; i++) {
        int8_t cx = x;
        x = y;
        y = -cx;
    }
}

} // end of namespace
