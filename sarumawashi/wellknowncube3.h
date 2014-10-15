/**
 * wellknowncube3.h
 * 
 * Extended of Cube3. Implemented some well-known sequences.
 * 
 * @author kotarot
 * @version 0.1 2014-10-16
 */

#ifndef __WELLKNOWNCUBE3_H__
#define __WELLKNOWNCUBE3_H__

#include "cube3.h"

namespace Sarumawashi {

class WellKnownCube3 : public Cube3 {
public:
    WellKnownCube3() {};
    ~WellKnownCube3() {};

    /** Sets the cube to a well-known state given by name. */
    void wellknown(std::string name);
};

} // end of namespace

#endif
